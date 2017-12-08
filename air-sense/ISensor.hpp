#pragma once

class ISensor {
public:
    virtual int init() = 0;
    virtual int read() = 0;

    int getId(int mask = 0xFFFF) const { return mask & _id; }

protected:
    void setId(int id) { _id = id; }

    int _id = 0;
};

enum SensorId {
    IDSenBME280IAQ = 1 << 0,
    IDSenBME680    = 1 << 1,
    IDSenDS18B20   = 1 << 2,
    IDSenALight    = 1 << 3,
    IDSenAMQ135    = 1 << 4
};
