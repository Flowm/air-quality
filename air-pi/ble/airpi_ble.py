from sensor_manager import SensorManager
from ble_controller import BleController, BleDelegate
import time

SENSOR_ADDR = "F0:C7:7F:94:7D:D1"
SENSOR_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"
SENSOR_HANDLE = 0x12

sensor_manager = SensorManager()
ble = BleController()


def on_new_data(data):
    sensor_manager.receive_raw_data(data)


def main():
    ble.set_read_delegate(BleDelegate(SENSOR_HANDLE, on_new_data))
    while not ble.connect(SENSOR_ADDR):
        print("Will retry connection...")
        time.sleep(5)
    ble.loop()


if __name__ == '__main__':
    main()
