from models.rxtxmessage import RxTxMessage


class TransmitMessage(RxTxMessage):
    def __init__(self, parent=None, can_id=None, message=None, time=None, dlc=None, data=None, cycle_time=None, count=None, trigger=None):
        super().__init__(parent, can_id, message, time, "TX",
                         dlc, data, cycle_time, count)
        self.trigger = trigger
