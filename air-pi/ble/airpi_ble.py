from sensor_manager import SensorManager
from ble_controller import BleController, BleDelegate
from mqtt import MqttBroker
import time

SENSOR_ADDR = "F0:C7:7F:94:7D:D1"
SENSOR_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"
SENSOR_HANDLE = 0x12
BROKER_IP = "localhost"
TOPIC_ENVIRONMENT = "home/env/"
TOPIC_DATASET = "dataset"


sensor_manager = SensorManager()
ble = BleController()
mqtt = MqttBroker(BROKER_IP)


def on_ble_data(data):
    sensor_manager.receive_raw_data(data)


def on_valid_data(data):
    print("New dataset received -> {}".format(data.decode()))
    mqtt.publish(TOPIC_ENVIRONMENT + TOPIC_DATASET, data)


def main():
    ble.set_read_delegate(BleDelegate(SENSOR_HANDLE, on_ble_data))
    sensor_manager.on_new_data = on_valid_data
    while not ble.connect(SENSOR_ADDR):
        print("Will retry connection...")
        time.sleep(5)
    ble.loop()


if __name__ == '__main__':
    main()