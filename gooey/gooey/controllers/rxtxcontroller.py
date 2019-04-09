from models.transmit_tree_model import TransmitTreeModel
from models.receive_tree_model import ReceiveTreeModel
from models.transmit_message import TransmitMessage
from can import Message
import datetime
import asyncio

class RxtxController():
    """ The rxtx controller, containing data for the Receive/Transmit tab
        :param `maincontroller`: A reference to the maincontroller.
        :param `receivetable`: A QAbstractItemModel, used to model the data for the receive table
        :param `transmittable`: A QAbstractItemModel, used to model the data for the transmit table
    """
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
        """ Transmits the message to the CAN device and populates the transmit table.
        
        Arguments:
            transmit_message {[Message]} -- A message object containing the CAN data.
        """

        # Build the Message object
        message = Message()
        message.arbitration_id = int(transmit_message.can_id, 16)
        message.data = bytes.fromhex(transmit_message.data)
        message.dlc = transmit_message.dlc

        # Calculate the cycle time for transmitting messages in ms
        cycle_time = int(transmit_message.cycle_time) / 1000

        loop = asyncio.get_event_loop()

        # Create a task, which is re-scheduled every cycle_time ms
        self.tasks[transmit_message.can_id] = loop.create_task(
            do_stuff_every_x_seconds(
                cycle_time, lambda: self.transmit_and_append(message, transmit_message)))

    def appendTransmitTable(self, message):
        """ Appends to the transmit table with the CAN message.
        
        Arguments:
            message {Message} -- A message object containing CAN data.
        """
        self.transmittable.insertRow(message)

    def appendReceiveTable(self, message):
        """ Appends to the receive table with the CAN message.
        
        Arguments:
            message {Message} -- A message object containing CAN data.
        """
        self.receivetable.insertRow(message)

    def appendReceiveSignal(self, parent, signal):
        """ Appends to the receive table under the given parent.
        
        Arguments:
            parent {Message} -- A message object where the signals will be appended to.
            signal {Dict} -- A dictionary which holds data from the decoded message
        """
        self.receivetable.insertChildRow(parent, signal)

    def appendTransmitSignal(self, parent, signal):
        """ Appends to the transmit table under the given parent.
        
        Arguments:
            parent {Message} -- A message object where the signals will be appended to.
            signal {Dict} -- A dictionary which holds data from the decoded message
        """
        self.transmittable.insertChildRow(parent, signal)

    async def transmit_and_append(self, message, transmit_message):
        """ Transmit the message to the device and append the message to the table.
        """
        await self.transmit(message)
        self.appendTransmitTable(transmit_message)

    async def transmit(self, message):
        """ Transmits the message to the CAN-D device asynchronously.
        
        Arguments:
            message {Message} -- A message object containing the CAN data.
        """
        print("Transmit: " + str(message.arbitration_id))
        if self.maincontroller.candbus is not None:
            self.maincontroller.candbus.send(message)


async def do_stuff_every_x_seconds(timeout, stuff):
    """ An asynchronous function that will call the closure every timeout milli-seconds.
    
    Arguments:
        timeout {float} -- The sleep time in milli-seconds.
        stuff {function} -- The function that is called every timeout milli-seconds.
    """
    while True:
        await asyncio.sleep(timeout)
        await stuff()
