/*
 * Simple air quality monitor
 *
 * Using the BME280 (temperature, humidity, pressure) and MQ135 (gas) sensors
 * for measurement and a Teensy 3.2 to read and print the data over USB serial.
 *
 */

#include <Adafruit_BME280.h>

#define MQ135_A 23

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA 1013.25

int mq135_data;

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
struct bme280_data {
  float temp;
  float humidity;
  float pressure;
  float altitude;
} bme_data;

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
  bme_data.temp = bme.readTemperature();
  bme_data.humidity = bme.readHumidity();
  bme_data.pressure = bme.readPressure() / 100.0F;
  bme_data.altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  mq135_data = analogRead(MQ135_A);

  Serial.printf(
      "%4.2f *C, %5.3f %%RH, %7.2f hPA, %6.2f m, %4d mq\n\r", // Readable
      //"%04.2f,%05.3f,%07.2f,%06.2f,%04d\n\r", // CSV
      bme_data.temp, bme_data.humidity, bme_data.pressure, bme_data.altitude, mq135_data);

  delay(100);
}
