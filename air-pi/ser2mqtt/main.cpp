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
    int cnt = 0;

    while (true) {
        // Publish every 100th measurement
        if (sensor.get_json(buf, sizeof(buf)) && !(cnt++ % 100)) {
            printf("Pub: %s\n", buf);
            mqtt.pub(topic, buf);

            if (mqtt.loop()) {
                mqtt.reconnect();
            }
        }
    }
    return 0;
}
