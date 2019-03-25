class Trace():
    def __init__(self, can_id=None, message=None, time=None, rxtx=None, msgtype=None, dlc=None, length=None, data=None, cycle_time=None):
        self.can_id = can_id
        self.message = message
        self.time = time

        # RX or TX
        self.rxtx = rxtx

        # FD or BRS?
        self.msgtype = msgtype

        self.dlc = dlc
        self.length = length
        self.data = data
        self.cycle_time = cycle_time
