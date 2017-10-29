#include "Arduino.h"

#define APIN_MQ135 A0
#define APIN_LIGHT A1

#define LINESZ 1024
#define BUFSZ 1024

class AQSensor {
public:
    AQSensor();
    void readAnalogSensors();
    const char* format(int counter=0);

    float temperature;
    float humidity;
    float pressure;
    float gas_resistance;

    uint16_t analog_mq135;
    uint16_t analog_light;

private:
    char line[BUFSZ];
    char buf[BUFSZ];
};
