#include "Wire.h"

#define IAQ_ADDR 0x5A

class Iaq {
  public:
    Iaq() { Wire.begin(); }

    void read() {
      Wire.requestFrom(IAQ_ADDR, 9);

      predict = (Wire.read()<<8 | Wire.read());
      status = Wire.read();
      resistance = (Wire.read()&0x00) | (Wire.read()<<16) | (Wire.read()<<8 | Wire.read());
      tvoc = (Wire.read()<<8 | Wire.read());
    }

    uint16_t predict;
    uint8_t status;
    int32_t resistance;
    uint16_t tvoc;
};
