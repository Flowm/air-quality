#include "Arduino.h"

// Select between BME680 and BME280 + IAQ
#define BME680

// Enable MQ135 analog gas sensor
//#define MQ135

#define LINESZ 256
#define BUFSZ 64

class AQSensor {
public:
    AQSensor();
    void initSensors();
    void readSensors();
    void readAnalogSensors();
    const char* format(int counter=0);

private:
    char line[LINESZ];
    char buf[BUFSZ];

    float temperature;
    float humidity;
    float pressure;
    float gas_resistance;

    uint16_t analog_mq135;
    uint16_t analog_light;

    float ds_temperature;
};
