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
    int sum = 0;
    int len = snprintf(buf, BUFSZ,
            "cnt=%05d"
            ",temp=%04.2f,humi=%05.3f,pres=%07.2f"
            ",gasp=%04d,gasr=%05.0f"
            ",amq=%04d"
            ",ali=%04d",
            counter,
            temperature, humidity, pressure,
            gas, gas_resistance,
            analog_mq135,
            analog_light
            );

    // Calculate checksum for transmission
    for (int i=0; i<len; i++) {
        sum += buf[i]*i;
    }
    sum = 0xFF & sum;
    if (len+11 < BUFSZ) {
        snprintf(buf+len, BUFSZ-len, ",chk=%03d\r\n", sum);
    }
    return &buf[0];
}
