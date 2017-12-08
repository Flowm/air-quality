#include "SenBME280IAQ.hpp"

int SenBME280IAQ::init() {
    Serial.println("BME init");
    if (bme.begin()) {
        setId(IDSenBME280IAQ);
        return 0;
    }
    return 1;
}

int SenBME280IAQ::read() {
    _temperature = bme.readTemperature();
    _humidity = bme.readHumidity();
    _pressure = bme.readPressure();
    _gasresistance = iaq.readGas();

    return 0;
}
