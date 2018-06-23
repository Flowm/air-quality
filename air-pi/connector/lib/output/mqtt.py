import paho.mqtt.client as mqtt

DEFAULT_IP = "localhost"
DEFAULT_PORT = 1883
DEFAULT_KEEPALIVE = 60


class MqttBroker:
    def __init__(self, ip=DEFAULT_IP, port=DEFAULT_PORT,
                 client_id=None, keepalive=DEFAULT_KEEPALIVE):
        self.client = mqtt.Client(client_id=client_id)
        self.client.on_connect = self.__on_connect
        self.client.connect(ip, port, keepalive)
        self.client.loop_start()

    def __on_connect(self, client, userdata, flags, rc):
        print("MqttBroker connected with result code " + str(rc))

    def publish(self, topic, data):
        self.client.publish(topic, data)
