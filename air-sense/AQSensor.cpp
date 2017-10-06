#include "AQSensor.hpp"

const char* AQSensor::format(int counter) {
    int sum = 0;
    int len = snprintf(buf, BUFSZ,
            "cnt=%05d,"
            "temp=%04.2f,humi=%05.3f,pres=%07.2f,"
            "gase=%04d,"
            "gasp=%04d,gasr=%05.2f",
            counter,
            temperature, humidity, pressure,
            gas_extra,
            gas, gas_resistance
            );

    // Calculate checksum for transmission
    for (int i=0; i<len; i++) {
        sum += buf[i]*i;
    }
    sum = 0xFF & sum;
    if (len+11 < BUFSZ) {
        snprintf(buf+len, BUFSZ-len, ",chk=%03d\n\r", sum);
    }
    return &buf[0];
}
