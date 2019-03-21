class Trace():
    def __init__(self, time=None, can_id=None, rxtx=None, msgtype=None, length=None, data=None, cycle_time=None):
        self.time = time
        self.can_id = can_id

        # RX or TX
        self.rxtx = rxtx

        # FD or BRS?
        self.msgtype = msgtype

        self.length = length
        self.data = data
        self.cycle_time = cycle_time
