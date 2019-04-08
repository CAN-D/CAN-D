from models.trace import Trace

class RxTxMessage(Trace):
    """ A parent class containing data for a Receive or Transmit message

        :param `parent`: The parent of the receive message.
        :param `can_id`: The arbitration_id of the CAN message.
        :param `message`: The decoded message name from the data.
        :param `time`: The time when the message was received.
        :param `rxtx`: Is the message a Receive (RX) or Transmit (TX)
        :param `dlc`: The length of the data field.
        :param `data`: Raw CAN data from the device.
        :param `cycle_time`: The time between this message was received and the last time it was received.
        :param `count`:  The number of times this message was received
    """
    def __init__(self, parent=None, can_id=None, message=None, time=None, rxtx=None, dlc=None, data=None, cycle_time=None, count=None):

        super().__init__(parent, can_id, message, time, rxtx,
                         dlc, data, cycle_time)
        self.count = count

    def properties(self, column):
        """ Return the value to be displayed on the given column index.
        """
        if column == 0:
            return self.can_id
        elif column == 1:
            return self.message
        elif column == 2:
            return self.dlc
        elif column == 3:
            return self.cycle_time
        elif column == 4:
            return self.count
        elif column == 5:
            return self.data
