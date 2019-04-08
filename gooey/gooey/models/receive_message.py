from models.rxtxmessage import RxTxMessage

class ReceiveMessage(RxTxMessage):
    """ The model for a received message.

        :param `parent`: The parent of the receive message.
        :param `can_id`: The arbitration_id of the CAN message.
        :param `message`: The decoded message name from the data.
        :param `time`: The time when the message was received.
        :param `dlc`: The length of the data field.
        :param `data`: Raw CAN data from the device.
        :param `cycle_time`: The time between this message was received and the last time it was received.
        :param `count`:  The number of times this message was received
    """
    def __init__(self, parent=None, can_id=None, message=None, time=None, dlc=None, data=None, cycle_time=None, count=None):
        super().__init__(parent, can_id, message, time, "RX",
                         dlc, data, cycle_time, count)
