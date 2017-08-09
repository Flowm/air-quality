#include "Mqtt.hpp"

#include <cstring>
#include <cstdio>

Mqtt::Mqtt(const char* id, const char* host, const int port, const int keepalive) : mosqpp::mosquittopp(id) {
        sem_init(&msg_sem, 0, 0);

        mosqpp::lib_init();
        connect(host, port, keepalive);
        loop_start();
}

Mqtt::~Mqtt() {
    while (want_write()) ;
    disconnect();
    loop_stop();
    mosqpp::lib_cleanup();
}

bool Mqtt::pub(const char* topic, const char* message) {
    int ret = publish(NULL, topic, strlen(message), message, 1, false);
    return (ret == MOSQ_ERR_SUCCESS);
}

bool Mqtt::sub(const char* topic) {
    int ret = subscribe(NULL, topic);
    return (ret == MOSQ_ERR_SUCCESS);
}

void Mqtt::read(char* buffer, size_t size) {
    strncpy(buffer, msg_buf, size);
}

void Mqtt::wait() {
    sem_wait(&msg_sem);
}

// Callbacks
void Mqtt::on_connect(int rc) {
    if (rc == 0) {
        printf("Mqtt: Connected\n");
    } else {
        printf("Mqtt: Connect failed\n");
    }
};

void Mqtt::on_disconnect(int rc) {
    printf("Mqtt: Disconnected\n");
};

void Mqtt::on_publish(int mid) {
    printf("Mqtt: Publish #%d\n", mid);
};

void Mqtt::on_message(const struct mosquitto_message* message) {
    char* msg = (char*) message->payload;
    printf("Mqtt: Message received %s\n", msg);
    strncpy(msg_buf, msg, sizeof(msg_buf));

    sem_post(&msg_sem);
}
