#pragma once

#include <Adafruit_BME280.h>
#include "SenIAQ.hpp"

#include "ISensor.hpp"

#define BME280_CS 10
#define BME280_MOSI 11
#define BME280_MISO 12
#define BME280_SCK 13

class SenBME280IAQ : public ISensor {
public:
    SenBME280IAQ() : bme(BME280_CS, BME280_MOSI, BME280_MISO, BME280_SCK) {}

    int init();
    int read();

    float temperature() const { return _temperature; }
    float humidity() const { return _humidity; }
    float pressure() const { return _pressure; }
    float gasresistance() const { return _gasresistance; }

private:
    Adafruit_BME280 bme;
    Iaq iaq;

    float _temperature;
    float _humidity;
    float _pressure;
    float _gasresistance;
};
