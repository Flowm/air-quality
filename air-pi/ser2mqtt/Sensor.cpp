#include "Sensor.hpp"

#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

Sensor::Sensor(const char *device) {
    fd = open(device, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        printf("Sensor: Failed to open %s", device);
        exit(1);
    }

    // Configure serial port
    struct termios options;
    tcgetattr(fd, &options);
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    options.c_ispeed = 9600;
    options.c_ospeed = 9600;
    tcsetattr(fd, TCSANOW, &options);

    printf("Sensor: Init successful\n");
}

Sensor::~Sensor() {
    close(fd);
}

int Sensor::get(char* line, size_t line_size) {
    char c;
    int pos = 0;
    while(read(fd, &c, 1)) {
        if (c == '\r') {
            strncpy(line, buf, line_size);
            return 0;
        } else if (c < LINE_SZ) {
            if (c == '\n') {
                buf[pos++] = '\0';
            } else {
                buf[pos++] = c;
            }
        }
    }

    return -1;
}
