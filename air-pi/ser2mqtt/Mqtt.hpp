#pragma once

#include <mosquittopp.h>
#include <semaphore.h>

class Mqtt : public mosqpp::mosquittopp
{
    public:
        Mqtt(const char* id, const char* host, const int port=1883, const int keepalive=60);
        ~Mqtt();

        bool pub(const char* topic, const char* message);
        bool sub(const char* topic);
        void read(char* buffer, size_t size);
        void wait();

    private:
        // Callbacks
        void on_connect(int rc);
        void on_disconnect(int rc);
        void on_publish(int mid);
        void on_message(const struct mosquitto_message* message);

        sem_t msg_sem;
        char msg_buf[20];
};
