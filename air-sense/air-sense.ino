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

#include "AQSensor.hpp"
#include <Adafruit_BME280.h>
#include "ams_iaq.h"

#define BME_CS 10
#define BME_MOSI 11
#define BME_MISO 12
#define BME_SCK 13
#define MQ135_A 14

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
Iaq iaq;
AQSensor aq;
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
    aq.temperature = bme.readTemperature();
    aq.humidity = bme.readHumidity();
    aq.pressure = bme.readPressure() / 100.0F;
    aq.gas_extra = analogRead(MQ135_A);

    if (iaq.read()) {
        aq.gas = iaq.readGas();
        aq.gas_resistance = iaq.readGasResistance();
    }

    // Format and print sensor data
    const char* buf = aq.format(counter++);
    Serial.print(buf);
    Serial1.print(buf);

    // Refresh interval
    delay(100);
}
