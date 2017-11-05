#from bluetooth import *
#from bluetooth.ble import DiscoveryService, GATTRequester, GATTResponse
#import pygatt

from bluepy import btle
from sensor_manager import SensorManager


class BleDelegate(btle.DefaultDelegate):
    def __init__(self, listen_handle, on_new_data):
        btle.DefaultDelegate.__init__(self)
        self.listen_handle = listen_handle
        self.on_new_data = on_new_data

    def handleNotification(self, cHandle, data):
        if cHandle == self.listen_handle:
            self.on_new_data(data)


class BleController:
    def __init__(self):
        self.connected_device = btle.Peripheral()

    def connect(self, address):
        try:
            self.connected_device.connect(address)
            self.get_characteristics()
            return True
        except btle.BTLEException:
            print("Connection to to {} failed".format(address))
            return False

    def get_characteristics(self):
        # TODO: implement precise print logic
        self.connected_device.getCharacteristics()
        pass

    def get_services(self):
        #TODO: implement
        pass

    def set_read_delegate(self, read_delegate):
        self.connected_device.setDelegate(read_delegate)

    def loop(self, forever=True, timeout=0.1):
        while True:
            self.connected_device.waitForNotifications(timeout)
            if not forever:
                return


# Pygatt example
#gatt = pygatt.GATTToolBackend()

#gatt.scan()
# try:
#     gatt.start(reset_on_start=True)
#     # gatt.reset()
#     device = gatt.connect(sensor_addr)
#     chars = device.discover_characteristics()
#     print(chars)
#     # device.subscribe(sensor_uuid, handle_data)
#
#     while True:
#         # data = device.char_read(0x12)
#         data = device.char_read(sensor_uuid)
#         print(data)
#         # time.sleep(10)
# except Exception as e:
#     print(e)
# finally:
#     gatt.stop()
#
# print("Ended")


