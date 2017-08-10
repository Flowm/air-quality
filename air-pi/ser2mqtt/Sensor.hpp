#pragma once

#include <cstdlib>

#define LINE_SZ 256

class Sensor
{
    public:
        Sensor(const char *device);
        ~Sensor();

        bool read_line();
        bool get_json(char* buf, int buf_sz);

    private:
        int fd;
        char linebuf[LINE_SZ];
};
