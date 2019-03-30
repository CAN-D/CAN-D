from models.rxtxmessage import RxTxMessage


class ReceiveMessage(RxTxMessage):
    def __init__(self, can_id=None, message=None, time=None, dlc=None, data=None, cycle_time=None, count=None):
        super().__init__(can_id, message, time, "RX",
                         dlc, data, cycle_time, count)
