from models.rxtxmessage import RxTxMessage


class ReceiveMessage(RxTxMessage):
    def __init__(self, can_id=None, message=None, time=None, dlc=None, length=None, data=None, cycle_time=None, count=None):
        super().__init__(can_id, message, time, "RX",
                         dlc, length, data, cycle_time, count)
