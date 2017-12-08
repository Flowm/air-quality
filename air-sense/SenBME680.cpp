#include "SenBME680.hpp"

int SenBME680::init() {
    Serial.println("BME init");
    if (!bme.begin()) {
        setId(IDSenBME680);
        return 0;
    }
    return 1;
}

int SenBME680::read() {
    bme.startConvert();
    delay(100);
    bme.update();

    _temperature = bme.readTemperature() / 100.0F;
    _humidity = bme.readHumidity() / 1000.0F;
    _pressure = bme.readPressure() / 100.0F;
    _gasresistance = bme.readGasResistance();

    return 0;
}
