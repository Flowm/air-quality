#!/usr/bin/env python3

from sensor_manager import SensorManager
from ble_controller import BleController, BleDelegate
from mqtt import MqttBroker
import json
import time

SENSOR_ADDR = "F0:C7:7F:94:7D:D1"
SENSOR_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"
SENSOR_HANDLE = 0x12
TOPIC_ENVIRONMENT = "home/env/"
TOPIC_DATASET = "dataset"
TOPIC_GET = "/raw"


sensor_manager = SensorManager()
ble = BleController()
mqtt = MqttBroker()


def on_ble_data(data):
    sensor_manager.receive_raw_data(data)


def on_valid_data(data):
    print("New dataset received -> {}".format(data))
    mqtt.publish(TOPIC_ENVIRONMENT + TOPIC_DATASET, json.dumps(data))


def on_sensor_data(sensor, data):
    mqtt.publish(TOPIC_ENVIRONMENT + sensor + TOPIC_GET, data)


def connect():
    while not ble.connect(SENSOR_ADDR):
        print("Will retry connection...")
        time.sleep(5)


def main():
    ble.set_read_delegate(BleDelegate(SENSOR_HANDLE, on_ble_data))
    sensor_manager.on_new_data = on_valid_data
    sensor_manager.on_sensor_data = on_sensor_data
    connect()
    while True:
        result = ble.loop()
        if not result:
            print("Set to not run forever. Shutting down down airpi_ble")
            break
        else:
            print("Error {} occurred".format(result.code))
            connect()


if __name__ == '__main__':
    main()
