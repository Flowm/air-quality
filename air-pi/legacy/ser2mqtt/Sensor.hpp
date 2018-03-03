#pragma once

#include <cstdlib>

#define LINE_SZ 256

class Sensor
{
    public:
        Sensor(const char *device);
        ~Sensor();

        bool get_json(char* buf, int buf_sz);

    private:
        bool read_line();
        bool verify_checksum();

        int fd;
        char linebuf[LINE_SZ];
};
