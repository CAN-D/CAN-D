from models.trace import Trace


class RxTxMessage(Trace):
    def __init__(self, can_id=None, message=None, time=None, rxtx=None, dlc=None, length=None, data=None, cycle_time=None, count=None):

        super().__init__(can_id, message, time, rxtx,
                         dlc, length, data, cycle_time)
        self.count = count
