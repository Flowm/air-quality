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
// Beacon parameters
#define MANUFACTURER_APPLE         0x4C
#define BEACON_UUID                "74-27-8B-DA-B6-44-45-20-8F-0C-72-0E-AF-05-99-35"
// #define BEACON_UUID                "01-12-23-34-45-56-67-78-89-9A-AB-BC-CD-DE-EF-F0"
#define BEACON_MAJOR               0x00
#define BEACON_MINOR               0x00
#define BEACON_RSSI_1M             -54

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
    ble.factoryReset();
    ble.setName("Bluefruit_m0");
    ble.iBeacon(MANUFACTURER_APPLE, BEACON_UUID, BEACON_MAJOR, BEACON_MINOR, BEACON_RSSI_1M);
    ble.reset();
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
