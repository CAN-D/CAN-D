from models.transmit_table_model import TransmitTableModel
from models.receive_table_model import ReceiveTableModel
from models.transmit_message import TransmitMessage
import datetime


class RxtxController():
    def __init__(self, receivetable=None, transmittable=None):
        if receivetable is not None:
            self.receivetable = receivetable
        else:
            self.receivetable = ReceiveTableModel()

        if transmittable is not None:
            self.transmittable = transmittable
        else:
            self.transmittable = TransmitTableModel()

    def transmitMessage(self, message):
        # TODO, call api to transmit message here
        self.appendTransmitTable(message)

    def appendTransmitTable(self, message):
        self.transmittable.insertRow(message)

    def appendReceiveTable(self, message):
        self.receivetable.insertRow(message)

    def setTest(self):
        newmsg = TransmitMessage(
            "CAN-ID1", "Message1", datetime.datetime.now().strftime("%H:%M:%S"), "FD,BRS", "DLC", 32, "Data", "cycle_time", 1, "Trigger")
        self.transmittable.messages.append(newmsg)
        newmsg2 = TransmitMessage(
            "CAN-ID2", "Message2", datetime.datetime.now().strftime("%H:%M:%S"), "FD,BRS", "DLC", 32, "Data", "cycle_time", 1, "Trigger")
        self.transmittable.messages.append(newmsg2)
