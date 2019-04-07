from models.transmit_tree_model import TransmitTreeModel
from models.receive_tree_model import ReceiveTreeModel
from models.transmit_message import TransmitMessage
from can import Message
import datetime
import asyncio


class RxtxController():
    def __init__(self, maincontroller, receivetable=None, transmittable=None):
        self.maincontroller = maincontroller
        if receivetable is not None:
            self.receivetable = receivetable
        else:
            self.receivetable = ReceiveTreeModel()

        if transmittable is not None:
            self.transmittable = transmittable
        else:
            self.transmittable = TransmitTreeModel()

        self.tasks = {}

    def transmitMessage(self, transmit_message):
        message = Message()
        message.arbitration_id = transmit_message.can_id
        message.data = transmit_message.data
        message.dlc = transmit_message.dlc

        cycle_time = int(transmit_message.cycle_time) / 1000
        loop = asyncio.get_event_loop()
        self.tasks[transmit_message.can_id] = loop.create_task(
            do_stuff_every_x_seconds(
                cycle_time, lambda: self.transmit(message)))

        self.appendTransmitTable(transmit_message)

    def appendTransmitTable(self, message):
        self.transmittable.insertRow(message)

    def appendReceiveTable(self, message):
        self.receivetable.insertRow(message)

    def appendReceiveSignal(self, parent, signal):
        self.receivetable.insertChildRow(parent, signal)

    def appendTransmitSignal(self, parent, signal):
        self.transmittable.insertChildRow(parent, signal)

    async def transmit(self, message):
        print("Transmit: " + message.arbitration_id)
        if self.maincontroller.candbus is not None:
            self.maincontroller.candbus.send(message)


async def do_stuff_every_x_seconds(timeout, stuff):
    while True:
        await asyncio.sleep(timeout)
        await stuff()
