#pragma once

class ISensor {
public:
    virtual int init() = 0;
    virtual int read() = 0;
    bool valid() const { return _valid; }

protected:
    bool _valid = false;
};
