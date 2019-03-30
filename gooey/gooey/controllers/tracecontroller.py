from models.trace_table_model import TraceTableModel
from models.trace import Trace


class TraceController():
    def __init__(self, tracetable=None, can_id=None, can_mask=None):
        if tracetable is not None:
            self.tracetable = tracetable
        else:
            self.tracetable = TraceTableModel()

        self.can_id = can_id
        self.can_mask = can_mask

    def appendTraceTable(self, message):
        self.tracetable.insertRow(message)
