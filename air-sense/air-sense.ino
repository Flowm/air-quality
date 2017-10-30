/*
 * Simple air quality monitor node
 *
 * Using the following sensors:
 * - BME280 (temperature, humidity, pressure)
 * - iAQ-core (CO2, TVOC)
 * Or alternatively:
 * - BME680 (temperature, humidity, pressure, gas)
 * Data is read periodically by a Teensy 3.2 and then printed over serial
 * console to USB and HM-11 BLE module.
 *
 */

#include "AQSensor.hpp"

AQSensor aq;
int counter = 0;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    delay(2000);
    aq.initSensors();
}

void loop() {
    aq.readSensors();

    // Format and print sensor data
    const char* buf = aq.format(counter++);
    Serial.print(buf);
    Serial1.print(buf);

    // Refresh interval
    delay(100);
}
