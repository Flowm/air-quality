#!/usr/bin/env python3

import functools
import sys
import time


class Sensor:
    def __init__(self, name):
        self.name = name
        self.data_timestamp = None
        self.on_sensor_data = None
        self.data = None

    def read_new_data(self, data):
        self.data_timestamp = time.time()
        self.data = data
        if self.on_sensor_data:
            self.on_sensor_data(self.name, self.data)


class SensorManager:
    def __init__(self):
        self.raw_data = bytearray()
        self.sensors = {}
        self.on_new_data = None
        self.on_sensor_data = None

    def __new_sensor(self, name):
        print("New sensor discovered")
        self.sensors[name] = Sensor(name)
        self.sensors[name].on_sensor_data = self.on_sensor_data

    def __parse_raw_data(self, raw_data):
        data = raw_data.strip()
        dataset = {}
        data = data.decode().split(',')
        for element in data:
            (key, value) = element.split('=')
            if key not in self.sensors:
                self.__new_sensor(key)
            self.sensors[key].read_new_data(value)
            dataset[key] = self.sensors[key].data
        dataset['timestamp'] = time.time()
        if self.on_new_data:
            self.on_new_data(dataset)

    def __verify_checksum(self, data):
        tmp = data
        chk_index = data.find(b',chk=')
        if chk_index < 0:
            return False
        checksum = data[chk_index + 5:chk_index + 8].decode()
        data = data[:chk_index].decode()
        try:
            checksum = int(checksum)
        except ValueError:
            return False
        val_sum = 0
        for i in range(len(data)):
            val_sum += (ord(data[i]) * (i+1))
        if (val_sum & 0xFF) != checksum:
            print("Fail -> Original: {}, Data: {}, Chk: {}, Sum: {}".format(tmp, data, checksum, val_sum))
        return (val_sum & 0xFF) == checksum

    def receive_raw_data(self, data):
        self.raw_data += data
        self.raw_data = self.raw_data.strip(b'\n')
        index = self.raw_data.find(b'\r')
        if index >= 0:
            data = self.raw_data[:index]
            if self.__verify_checksum(data):
                self.__parse_raw_data(data)
            self.raw_data = self.raw_data[index + 1:]


