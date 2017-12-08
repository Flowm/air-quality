#pragma once

#include <OneWire.h>

#include "ISensor.hpp"

#define DS18B20_PIN 9

class SenDS18B20 : public ISensor {
public:
    SenDS18B20() : ds(9) {}

    int init();
    int read();

    float temperature() const { return _temperature; }

private:
    OneWire ds;
    byte data[12];
    byte addr[8];
    byte type_s;

    float _temperature;
};
