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

#define SER1 Serial1 // Serial port 1
#define SER2 Serial2 // Serial port 2
//#define SER2 Serial // USB Serial

AQSensor aq;
int counter = 0;

void setup() {
    SER1.begin(9600);
    SER2.begin(9600);
    delay(2000);
    aq.initSensors();
}

void loop() {
    aq.readSensors();

    const char* buf = aq.format(counter++);
    SER1.print(buf);
    SER2.print(buf);

    // Refresh interval
    delay(100);
}
