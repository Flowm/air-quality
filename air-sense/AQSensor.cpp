#include "AQSensor.hpp"

AQSensor::AQSensor() {
    pinMode(APIN_MQ135, INPUT);
    pinMode(APIN_LIGHT, INPUT);
    analogReadAveraging(32);
}

void AQSensor::readAnalogSensors() {
  analog_mq135 = analogRead(APIN_MQ135);
  analog_light = analogRead(APIN_LIGHT);
}

const char* AQSensor::format(int counter) {
    line[0] = '\0';
    snprintf(buf, BUFSZ, "cnt=%05d", counter);
    strlcat(line, buf, LINESZ);

    if (temperature) {
        snprintf(buf, BUFSZ, ",temp=%04.2f,humi=%05.3f,pres=%07.2f", temperature, humidity, pressure);
        strlcat(line, buf, LINESZ);
    }

    if (gas_resistance) {
        snprintf(buf, BUFSZ, ",gasr=%05.0f", gas_resistance);
        strlcat(line, buf, LINESZ);
    }

    if (analog_mq135) {
        snprintf(buf, BUFSZ, ",amq=%04d", analog_mq135);
        strlcat(line, buf, LINESZ);
    }

    if (analog_light) {
        snprintf(buf, BUFSZ, ",ali=%04d", analog_light);
        strlcat(line, buf, LINESZ);
    }

    // Calculate checksum for transmission
    int sum = 0;
    for (size_t i = 0; i < strlen(buf); i++) {
        sum += line[i]*i;
    }
    sum = 0xFF & sum;

    snprintf(buf, BUFSZ, ",chk=%03d\r\n", sum);
    strlcat(line, buf, LINESZ);

    return &line[0];
}
