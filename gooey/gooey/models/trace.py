class Trace():
    def __init__(self, can_id=None, message=None, time=None, rxtx=None, dlc=None, data=None, cycle_time=None):
        self.can_id = can_id
        self.message = message
        self.time = time

        # RX or TX
        self.rxtx = rxtx

        self.dlc = dlc
        self.data = data
        self.cycle_time = cycle_time
