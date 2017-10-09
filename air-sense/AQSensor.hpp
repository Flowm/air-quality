#include "Arduino.h"

#define APIN_MQ135 A0
#define APIN_LIGHT A1

#define BUFSZ 1024

class AQSensor {
public:
    AQSensor();
    void readAnalogSensors();
    const char* format(int counter=0);

    float temperature;
    float humidity;
    float pressure;
    uint16_t gas;
    uint16_t gas_extra;
    float gas_resistance;

    uint16_t analog_mq135;
    uint16_t analog_light;

private:
    char buf[BUFSZ];
};
