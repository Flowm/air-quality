#include "Arduino.h"

// Select between BME680 and BME280 + IAQ
#define BME680

#ifdef BME680
#include "SenBME680.hpp"
#include "SenDS18B20.hpp"
#endif

// Enable MQ135 analog gas sensor
//#define MQ135

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
    SenBME680 bme;
    SenDS18B20 ow;

    char line[LINESZ];
    char buf[BUFSZ];

    uint16_t analog_mq135;
    uint16_t analog_light;
};
