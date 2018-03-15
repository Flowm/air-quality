import time
import logging


def str2digit(value):
    try:
        return int(value)
    except ValueError:
        try:
            return float(value)
        except ValueError:
            return None


class AQParse:
    type = "env"
    cnt = 0

    def parse_packet(self, packet):
        self.cnt += 1
        #if not self.__verify_checksum(packet):
        #    return
        if self.cnt < 10:
            return
        self.cnt = 0

        yield ("%s-raw" % self.type, packet)
        try:
            for entry in packet.split(','):
                name, value = entry.split('=')
                value = str2digit(value)
                if value:
                    yield ("%s/%s" % (self.type, name), value)
        except ValueError:
            logging.info("Invalid data in packet: %s" % packet)
            return


    def __verify_checksum(self, packet):
        data, checksum = self.__split_checksum(packet)
        try:
            checksum = int(checksum)
        except ValueError:
            return False

        val_sum = 0
        for i in range(len(data)):
            val_sum += (ord(data[i]) * (i+1))
        if (val_sum & 0xFF) != checksum:
            logging.info("Checksum invalid Data: %s Chk: %s Calc: %s" % (data, checksum, val_sum & 0xFF))
        return (val_sum & 0xFF) == checksum


    def __split_checksum(self, packet):
        chk_index = packet.find("chk=")
        if chk_index < 0:
            return None, None
        checksum = packet[chk_index + 4:]
        data = packet[:chk_index]
        return data, checksum
