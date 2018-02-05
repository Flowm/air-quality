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

#define SER1 Serial1 // Serial port 1
#define SERU Serial  // USB Serial
#ifndef SERU
#include <Snooze.h>
SnoozeTimer timer;
SnoozeBlock config(timer);
#endif

#ifdef _VARIANT_ARDUINO_ZERO_
#define BLUEFRUIT
#include "src/bluefruit/BluefruitController.hpp"
BluefruitController ble;
#endif

AQManager aq;
int counter = 0;
const int refreshInterval = 500;

void setup() {
    SER1.begin(9600);
#ifdef SERU
    SERU.begin(9600);
#endif
#ifdef BLUEFRUIT
    ble.setup();
#endif
    delay(2000);
    aq.init();
}

void loop() {
    aq.read();
    const char* buf = aq.format(counter++);
    SER1.print(buf);
#ifdef BLUEFRUIT  // Bluefruit
    ble.sendData(buf);
    delay(refreshInterval);
#elif defined(SERU)  // HM-11 module
    SERU.print(buf);
    delay(refreshInterval);
#else  // Teensy power saving
    timer.setTimer(refreshInterval);
    Snooze.deepSleep(config);
#endif
}
