from models.transmit_table_model import TransmitTableModel
from models.receive_table_model import ReceiveTableModel
from models.transmit_message import TransmitMessage


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

    def appendTransmitTable(self, message):
        num_msgs = self.transmittable.rowCount()
        self.transmittable.insertRow(message, num_msgs)

    def appendReceiveTable(self, message):
        num_msgs = self.receivetable.rowCount()
        self.receivetable.insertRow(message, num_msgs)

    def setTest(self):
        newmsg = TransmitMessage(
            "Test1", "DLC", "Data", "cycle_time", "Count", "Trigger")
        self.transmittable.messages.append(newmsg)
        newmsg2 = TransmitMessage(
            "Test2", "DLC", "Data", "cycle_time", "Count", "Trigger")
        self.transmittable.messages.append(newmsg2)
