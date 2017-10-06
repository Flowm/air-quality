#include "Wire.h"

#define IAQ_ADDR 0x5A

class Iaq {
  public:
    Iaq() { Wire.begin(); }

    bool read() {
      Wire.requestFrom(IAQ_ADDR, 9);

      uint16_t predict = (Wire.read()<<8 | Wire.read());
      uint8_t status = Wire.read();
      uint32_t resistance = (Wire.read()&0x00) | (Wire.read()<<16) | (Wire.read()<<8 | Wire.read());
      uint16_t tvoc = (Wire.read()<<8 | Wire.read());

      if (!status) {
        this->predict = predict;
        this->resistance = resistance;
        this->tvoc = tvoc;
        return true;
      }
      return false;
    }

    float readGas() {
      return predict;
    }
    float readGasResistance() {
      return resistance;
    }
    float readGasTvoc() {
      return tvoc;
    }

    uint16_t predict;
    int32_t resistance;
    uint16_t tvoc;
};
