#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "Mqtt.hpp"

int main(int argc, char *argv[]) {
    Mqtt mqtt("rpi", "localhost");
    char buf[20];

    printf("ser2mqtt: Start\n");

    mqtt.sub("ping");

    while (true) {
        int res = mqtt.loop();
        if (res) {
            mqtt.reconnect();
        }
        usleep(1e5);

        //mqtt.wait();
        //mqtt.read(buf, sizeof(buf));
        mqtt.pub("pong", buf);
    }

    return 0;
}
