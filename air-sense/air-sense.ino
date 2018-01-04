/*
 * Simple air quality monitor node
 *
 * Using the following sensors:
 * - BME280 (temperature, humidity, pressure)
 * - iAQ-core (CO2, TVOC)
 * Or alternatively:
 * - BME680 (temperature, humidity, pressure, gas)
 *
 * Required libs:
 * - duff2013/Snooze
 * - DFRobot/DFRobot_BME680
 * - adafruit/Adafruit_Sensor
 * - adafruit/Adafruit_BME280_Library
 *
 * Data is read periodically by a Teensy 3.2 and then printed over serial
 * console to USB and HM-11 BLE module.
 */

#include "AQManager.hpp"
#include "src/bluefruit/BluefruitController.hpp"

#define SER1 Serial1 // Serial port 1
#define SERU Serial  // USB Serial

#ifndef SERU
#include <Snooze.h>
SnoozeTimer timer;
SnoozeBlock config(timer);
#endif

#ifdef _VARIANT_ARDUINO_ZERO_
BluefruitController ble;
#endif

AQManager aq;
int counter = 0;

void setup() {
    SER1.begin(9600);
#ifdef SERU
    SERU.begin(9600);
#endif
    delay(2000);
#ifdef _VARIANT_ARDUINO_ZERO_
    ble.setup();
    ble.factoryReset();
    ble.setName("Bluefruit_m0");
    ble.reset();
#endif
    aq.init();

}

void loop() {
    aq.read();

    const char* buf = aq.format(counter++);
    SER1.print(buf);

    //Bluefruit only execution
#ifdef _VARIANT_ARDUINO_ZERO_
    ble.sendData(buf);
#else
#ifdef SERU
    //HM-11 module
    SERU.print(buf);
    delay(500);
#else
    // Refresh interval
    timer.setTimer(500);
    Snooze.deepSleep(config);
#endif
#endif
}
