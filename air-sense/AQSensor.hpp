#include "Arduino.h"

#define BUFSZ 1024

class AQSensor {
public:
    const char* format(int counter=0);

    float temperature;
    float humidity;
    float pressure;
    uint16_t gas_extra;
    uint16_t gas;
    float gas_resistance;

private:
    char buf[BUFSZ];
};
