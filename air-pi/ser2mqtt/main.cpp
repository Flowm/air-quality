#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "Mqtt.hpp"
#include "Sensor.hpp"

int main(int argc, char *argv[]) {
    Mqtt mqtt("rpi", "localhost");
    Sensor sensor("/dev/serial0");

    char buf[200];

    printf("ser2mqtt: Start\n");

    mqtt.sub("ping");

    while (true) {
        //int res = mqtt.loop();
        //if (res) {
        //    mqtt.reconnect();
        //}

        sensor.get(buf, sizeof(buf));
        printf("S: %s\n", buf);

        //mqtt.wait();
        //mqtt.read(buf, sizeof(buf));
        //mqtt.pub("pong", buf);
    }

    return 0;
}
