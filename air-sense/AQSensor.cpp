#include "AQSensor.hpp"

#ifdef BME680
#include <DFRobot_BME680_I2C.h>
#define BME_ADDR 0x77
DFRobot_BME680_I2C bme(BME_ADDR);
DFRobot_BME680_I2C* gas = &bme;

# else // BME280 + IAQ
#include <Adafruit_BME280.h>
#include "ams_iaq.h"

Adafruit_BME280 bme(10, 11, 12, 13);
Iaq iaq;
Iaq* gas = &iaq;
#endif

#define APIN_MQ135 A0
#define APIN_LIGHT A1

AQSensor::AQSensor() {
    pinMode(APIN_MQ135, INPUT);
    pinMode(APIN_LIGHT, INPUT);
    analogReadAveraging(32);
}

void AQSensor::initSensors() {
    Serial.println("BME init");
    if (!bme.begin()) {
        while (1) {
            Serial.println("BME init failed");
            delay(1000);
        }
    }
}

void AQSensor::readSensors() {
#ifdef BME680
    bme.startConvert();
    delay(100);
    bme.update();
#endif // BME680

    temperature = bme.readTemperature();
    humidity = bme.readHumidity();
    pressure = bme.readPressure() / 100.0F;
    gas_resistance = gas->readGasResistance();

    readAnalogSensors();
}

void AQSensor::readAnalogSensors() {
#ifdef MQ135
    analog_mq135 = analogRead(APIN_MQ135);
#endif
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
