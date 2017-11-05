import functools
import sys
import time


class Sensor:
    def __init__(self, name):
        self.name = name
        self.data_timestamp = None
        self.data = None

    def read_new_data(self, data):
        self.data_timestamp = time.time()
        self.data = data


class SensorManager:
    def __init__(self):
        self.raw_data = bytearray()
        self.sensors = {}
        self.on_new_data = None

    def __parse_raw_data(self, raw_data):
        data = raw_data.strip()
        if self.on_new_data:
            self.on_new_data(data.decode())
        data = data.split(',')
        for element in data:
            (key, value) = element.split('=')
            if key not in self.sensors:
                print("New sensor discovered")
                self.sensors[key] = Sensor(key)
            self.sensors[key].read_new_data(value)

    def __verify_checksum(self, data):
        chk_index = data.find(b',chk=')
        if chk_index < 0:
            return False
        checksum = data[chk_index + 5:].decode()
        data = data[:chk_index].decode()
        try:
            checksum = int(checksum)
        except ValueError:
            return False
        val_sum = 0
        for i in range(len(data)):
            val_sum += (ord(data[i]) * (i+1))
        return (val_sum & 0xFF) == checksum

    def receive_raw_data(self, data):
        self.raw_data += data.lstrip(b'\n')
        index = self.raw_data.find(b'\r')
        if index >= 0:
            data = self.raw_data[:index]
            if self.__verify_checksum(data):
                self.__parse_raw_data(data)
            self.raw_data = self.raw_data[index + 1:]

