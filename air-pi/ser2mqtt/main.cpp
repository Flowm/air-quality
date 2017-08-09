#include <cstring>
#include <cstdio>

#include "Mqtt.hpp"

int main(int argc, char *argv[]) {
    Mqtt mqtt("rpi", "localhost");
    char buf[20];

    printf("ser2mqtt: Start\n");

    mqtt.sub("ping");

    while (true) {
        mqtt.wait();
        mqtt.read(buf, sizeof(buf));
        mqtt.pub("pong", buf);
    }

    return 0;
}
