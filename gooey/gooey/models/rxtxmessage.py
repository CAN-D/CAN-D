from models.trace import Trace


class RxTxMessage(Trace):
    def __init__(self, parent=None, can_id=None, message=None, time=None, rxtx=None, dlc=None, data=None, cycle_time=None, count=None):

        super().__init__(parent, can_id, message, time, rxtx,
                         dlc, data, cycle_time)
        self.count = count

    def properties(self, column):
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
