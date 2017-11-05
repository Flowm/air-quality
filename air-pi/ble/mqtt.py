import paho.mqtt.client as mqtt
import re
import subprocess
import sys
import time

UPDATE_RATE = 1  # seconds
CLIENT_ID = "eac9c9686e75475c3286f5c7224ef3d359b30cf3"
DEFAULT_PORT = 1883
DEFAULT_KEEPALIVE = 60


class MqttBroker:
    def __init__(self, ip, port=DEFAULT_PORT, keepalive=DEFAULT_KEEPALIVE):
        self.client = mqtt.Client(client_id=CLIENT_ID)
        self.client.on_connect = self.__on_connect
        self.client.connect(ip, port, keepalive)
        self.client.loop_start()

    def __on_connect(self, client, userdata, flags, rc):
        print("Connected with result code " + str(rc))

    def publish(self, topic, data):
        self.client.publish(topic, data)


# client = mqtt.Client(client_id=CLIENT_ID)
# client.on_connect = on_connect
# client.connect(MQTT_IP, 1883, 60)
# client.loop_start()

# starttime = time.time()
# while True:
#     client.publish("home/env/raw/something", data)
#
#     time.sleep(UPDATE_RATE - ((time.time() - starttime) % UPDATE_RATE))