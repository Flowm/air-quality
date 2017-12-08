#pragma once

#include <DFRobot_BME680_I2C.h>

#include "ISensor.hpp"

#define BME_ADDR 0x77

class SenBME680 : public ISensor {
public:
    SenBME680() : bme(BME_ADDR) {}

    int init();
    int read();

    float temperature() const { return _temperature; }
    float humidity() const { return _humidity; }
    float pressure() const { return _pressure; }
    float gasresistance() const { return _gasresistance; }

private:
    DFRobot_BME680_I2C bme;

    float _temperature;
    float _humidity;
    float _pressure;
    float _gasresistance;
};
