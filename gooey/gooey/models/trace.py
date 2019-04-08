from models.treeitem import TreeItem

class Trace(TreeItem):
    """ The base model for data coming in from the CAN-D device.

        :param `parent`: The parent of the receive message.
        :param `can_id`: The arbitration_id of the CAN message.
        :param `message`: The decoded message name from the data.
        :param `time`: The time when the message was received.
        :param `rxtx`: Is the message a Receive (RX) or Transmit (TX)
        :param `dlc`: The length of the data field.
        :param `data`: Raw CAN data from the device.
        :param `cycle_time`: The time between this message was received and the last time it was received.
    """
    def __init__(self, parent=None, can_id=None, message=None, time=None, rxtx=None, dlc=None, data=None, cycle_time=None):
        super().__init__(self, parent)
        self.can_id = can_id
        self.message = message
        self.time = time

        # RX or TX
        self.rxtx = rxtx

        self.dlc = dlc
        self.data = data
        self.cycle_time = cycle_time
