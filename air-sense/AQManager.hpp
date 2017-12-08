#include "Arduino.h"

// Select between BME680 and BME280 + IAQ
#define BME680

#ifdef BME680
#include "SenBME680.hpp"
#else // BME280 + IAQ
#include "SenBME280IAQ.hpp"
#endif

#include "SenDS18B20.hpp"

#define LINESZ 256
#define BUFSZ 64

class AQManager {
public:
    AQManager();
    void init();
    void read();
    void readAnalogSensors();
    const char* format(int counter=0);

private:
#ifdef BME680
    SenBME680 bme;
#else // BME280 + IAQ
    SenBME280IAQ bme;
#endif
    SenDS18B20 ow;

    char line[LINESZ];
    char buf[BUFSZ];

    uint16_t analog_mq135;
    uint16_t analog_light;
};
