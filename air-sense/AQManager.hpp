#pragma once

#include "Arduino.h"

// Comment the line below to use BME280 + IAQ instead of BME680
#define BME680

#ifdef BME680
#include "SenBME680.hpp"
#else // BME280 + IAQ
#include "SenBME280IAQ.hpp"
#endif

#include "SenDS18B20.hpp"
#include "SenAnalog.hpp"

#define LINESZ 256
#define BUFSZ 64

class AQManager {
public:
    void init();
    void read();

    const char* format(int counter=0);

private:
#ifdef BME680
    SenBME680 bme;
#else // BME280 + IAQ
    SenBME280IAQ bme;
#endif
    SenDS18B20 ds;
    SenAnalog an;

    char line[LINESZ];
    char buf[BUFSZ];
};
