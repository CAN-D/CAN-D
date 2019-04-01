from models.transmit_tree_model import TransmitTreeModel
from models.receive_tree_model import ReceiveTreeModel
from models.transmit_message import TransmitMessage
import datetime


class RxtxController():
    def __init__(self, receivetable=None, transmittable=None):
        if receivetable is not None:
            self.receivetable = receivetable
        else:
            self.receivetable = ReceiveTreeModel()

        if transmittable is not None:
            self.transmittable = transmittable
        else:
            self.transmittable = TransmitTreeModel()

    def transmitMessage(self, message):
        # TODO, call api to transmit message here
        self.appendTransmitTable(message)

    def appendTransmitTable(self, message):
        self.transmittable.insertRow(message)

    def appendReceiveTable(self, message):
        self.receivetable.insertRow(message)

    def appendReceiveSignal(self, parent, signal):
        self.receivetable.insertChildRow(parent, signal)

    def appendTransmitSignal(self, parent, signal):
        self.transmittable.insertChildRow(parent, signal)
