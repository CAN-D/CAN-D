from models.treeitem import TreeItem


class Trace(TreeItem):
    def __init__(self, parent=None, can_id=None, message=None, time=None, rxtx=None, dlc=None, data=None, cycle_time=None):
        super().__init__(self, parent)
        self.can_id = can_id
        self.message = message
        self.time = time

        # RX or TX
        self.rxtx = rxtx

        self.dlc = dlc
        self.data = data
        self.cycle_time = cycle_time
