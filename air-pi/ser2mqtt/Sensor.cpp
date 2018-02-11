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

bool Sensor::read_line() {
    char c;
    int pos = 0;
    while(read(fd, &c, 1)) {
        if (c == '\n') {
            return verify_checksum();
        } else if (pos < LINE_SZ) {
            if (c == '\r') {
                linebuf[pos++] = '\0';
            } else {
                linebuf[pos++] = c;
            }
        }
    }
    return false;
}

bool Sensor::verify_checksum() {
    char* chk = strstr(linebuf, ",chk=");
    if (!chk)
        return false;

    // Retrieve checksum from string
    char* k = strtok(chk, "=");
    char* v = strtok(NULL, "=");
    if (!k || !v)
        return false;
    char chk_recv = strtol(v, NULL, 10);

    // Calculate checksum from string
    char chk_calc = 0;
    for (int i=0; i<chk-linebuf; i++) {
        chk_calc += linebuf[i]*i;
    }

    // Data string ends where checksum starts
    *chk = '\0';

    //printf("CHK: recv=%d calc=%d\n", chk_recv, chk_calc);
    if (chk_recv != chk_calc)
        return false;

    return true;
}

bool Sensor::get_json(char* buf, int buf_sz) {
    if (!read_line()) {
        return false;
    }

    char* key[20] = {};
    char* val[20] = {};
    unsigned int idx = 0;

    // Extract key ptrs
    key[idx] = strtok(linebuf, ",");
    while (key[idx] && idx < sizeof(key)) {
        idx++;
        key[idx] = strtok(NULL, ",");
    }

    // Loop over keys to obtain values
    for (unsigned int i = 0; i < idx; i++) {
        strtok(key[i], "=");
        if (char* v = strtok(NULL, "=")) {
            // Remove leading zeros for valid json
            while (*v && *(v+1) && *v == '0') {
                v++;
            }
            // Save value
            val[i] = v;
            //printf("%d: %s:%s\n", i, key[i], val[i]);
        }
    }
    //printf("\n");

    // Create json string
    int cnt = snprintf(buf, buf_sz, "{ ");
    for (unsigned int i = 0; i < idx; i++) {
        // Abort without enough space
        if (buf_sz-cnt < 4) {
            return false;
        }

        // Ignore keys without value
        if (!key[i] || !val[i]) {
            continue;
        }

        // Add key value pair to json string
        if (i)
            cnt += snprintf(buf+cnt, buf_sz-cnt, ", ");
        cnt += snprintf(buf+cnt, buf_sz-cnt, "\"%s\": %s", key[i], val[i]);
    }
    // Abort without enough space
    if (buf_sz-cnt < 2) {
        return false;
    }
    cnt += snprintf(buf+cnt, buf_sz-cnt, " }");

    return true;
}
