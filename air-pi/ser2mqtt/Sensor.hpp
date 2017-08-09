#pragma once

#include <cstdlib>

#define LINE_SZ 256

class Sensor
{
    public:
        Sensor(const char *device);
        ~Sensor();

        int get(char* buf, size_t buf_size);

    private:
        int fd;
        char buf[LINE_SZ];
};
