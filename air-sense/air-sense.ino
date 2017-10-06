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

// Select between BME680 and BME280 + IAQ
#define BME680

#include "AQSensor.hpp"

#ifdef BME680
#include <DFRobot_BME680_I2C.h>
#define BME_ADDR 0x77
DFRobot_BME680_I2C bme(BME_ADDR);
DFRobot_BME680_I2C* gas = &bme;

# else // BME280 + IAQ
#include <Adafruit_BME280.h>
#include "ams_iaq.h"

#define BME_CS 10
#define BME_MOSI 11
#define BME_MISO 12
#define BME_SCK 13

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
Iaq iaq;
Iaq* gas = &iaq;
#endif

AQSensor aq;
int counter = 0;

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600);
    delay(2000);

    // Setup BME
    Serial.println("BME init");
    if (!bme.begin()) {
        while (1) {
            Serial.println("BME init failed");
            delay(1000);
        }
    }
}

void loop() {
#ifdef BME680
    bme.startConvert();
    delay(1);
#endif // BME680

    aq.temperature = bme.readTemperature();
    aq.humidity = bme.readHumidity();
    aq.pressure = bme.readPressure() / 100.0F;
    aq.gas = gas->readGas();
    aq.gas_resistance = gas->readGasResistance();
    aq.readAnalogSensors();

    // Format and print sensor data
    const char* buf = aq.format(counter++);
    Serial.print(buf);
    Serial1.print(buf);

    // Refresh interval
    delay(100);
}
