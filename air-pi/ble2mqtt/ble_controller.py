from bluepy import btle


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
            try:
                self.connected_device.waitForNotifications(timeout)
            except btle.BTLEException as e:
                return e
            if not forever:
                return None
