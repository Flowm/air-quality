/*
 * Simple air quality monitor node
 *
 * Using the following sensors:
 * - BME280 (temperature, humidity, pressure)
 * - MQ135 (gas)
 * - iAQ-core (CO2, TVOC)
 * Data is read periodically by a Teensy 3.2 and then printed over serial
 * console to USB and HM-11 BLE module.
 *
 */

#include <Adafruit_BME280.h>
#include "ams_iaq.h"

#define BME_CS 10
#define BME_MOSI 11
#define BME_MISO 12
#define BME_SCK 13
#define MQ135_A 14

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
Iaq iaq;

struct sensor_data {
  float temp;
  float humidity;
  float pressure;
  int mq135;
} sdata;

#define BUFSZ 1024
char buf[BUFSZ];
int counter = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  delay(2000);

  // Setup BME280
  Serial.println("BME280 init");
  if (!bme.begin()) {
    while (1) {
      Serial.println("BME280 init failed");
      delay(1000);
    }
  }

  // Setup MQ135
  pinMode(MQ135_A, INPUT);
}

void loop() {
  // Read sensor data
  sdata.temp = bme.readTemperature();
  sdata.humidity = bme.readHumidity();
  sdata.pressure = bme.readPressure() / 100.0F;
  sdata.mq135 = analogRead(MQ135_A);
  iaq.read();

  // Prepare sensor data
  int sum = 0;
  int len = snprintf(buf, BUFSZ,
      "counter=%05d,"
      "temperature=%04.2f,humidity=%05.3f,pressure=%07.2f,mq135=%04d,"
      "iaqs=%02d,co2=%05d,tvoc=%05d",
      counter++,
      sdata.temp, sdata.humidity, sdata.pressure, sdata.mq135,
      iaq.status, iaq.predict, iaq.tvoc
  );

  // Calculate checksum for transmission
  for (int i=0; i<len; i++) {
    sum += buf[i]*i;
  }
  sum = 0xFF & sum;
  if (len+11 < BUFSZ) {
    snprintf(buf+len, BUFSZ-len,
        ",chk=%03d"
        "\n\r",
        sum
      );
  }

  // Print sensor data
  Serial.print(buf);
  Serial1.print(buf);

  // Refresh interval
  delay(100);
}
