from enum import Enum


class ConnectionType(Enum):
    USB = 1
    WIRELESS = 2


class Connection():
    def __init__(self, name=None, type=None, bitrate=None, clk_freq=None, connection=None):
        self.name = name
        self.type = ConnectionType.USB
        self.bitrate = bitrate
        self.clk_freq = clk_freq
        self.is_connected = False
        if (connection != None):
            self.connection = connection
            self.is_connected = True

    def connect(self):
        # TODO
        return

    def disconnect(self):
        # TODO
        return

    def setBitRate(self, bitrate):
        self.bitrate = bitrate

    def setClockFrequency(self, clk_freq):
        self.clk_freq = clk_freq

    def transmitMessage(self, message):
        # TODO
        return

    def receiveMessage(self, message):
        # TODO
        return
