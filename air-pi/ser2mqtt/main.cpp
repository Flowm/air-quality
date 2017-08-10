#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "Mqtt.hpp"
#include "Sensor.hpp"

const char* topic = "sensor/air-quality";

int main() {
    Mqtt mqtt("rpi", "localhost");
    Sensor sensor("/dev/serial0");
    char buf[256];

    while (true) {
        if (mqtt.loop()) {
            mqtt.reconnect();
        }

        sensor.get_json(buf, sizeof(buf));
        printf("Pub: %s\n", buf);
        mqtt.pub(topic, buf);
    }

    return 0;
}
