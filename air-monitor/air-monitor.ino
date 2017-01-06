/*
 * Simple air quality monitor
 *
 * Using the BME280 (temperature, humidity, pressure) and MQ135 (gas) sensors
 * for measurement and a Teensy 3.2 to read and print the data over USB serial.
 *
 */

#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define MQ135_A 23

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

struct sensor_data {
  float temp;
  float humidity;
  float pressure;
  int mq135;
} sdata;
int counter = 0;

void setup() {
  Serial.begin(115200);

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

  // Print sensor data
  Serial.printf(
      "counter=%05d,temperature=%04.2f,humidity=%05.3f,pressure=%07.2f,mq135=%04d\n\r",
      counter++, sdata.temp, sdata.humidity, sdata.pressure, sdata.mq135);

  // Refresh interval
  delay(100);
}
