#pragma once

#include "Arduino.h"

#include "ISensor.hpp"

#define APIN_LIGHT A1
//#define APIN_MQ135 A2

class SenAnalog : public ISensor {
public:
    SenAnalog() {}

    int init();
    int read();

    uint16_t light() const { return _light; }
    uint16_t mq135() const { return _mq135; }

private:
    uint16_t _light;
    uint16_t _mq135;
};
