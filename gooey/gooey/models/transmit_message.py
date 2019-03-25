from models.rxtxmessage import RxTxMessage


class TransmitMessage(RxTxMessage):
    def __init__(self, can_id=None, message=None, time=None, msgtype=None, dlc=None, length=None, data=None, cycle_time=None, count=None, trigger=None):
        super().__init__(can_id, message, time, "TX",
                         msgtype, dlc, length, data, cycle_time, count)
        self.trigger = trigger
