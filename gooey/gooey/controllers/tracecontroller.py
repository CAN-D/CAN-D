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

    def setTest(self):
        newmsg = Trace("18F00200h", "MSG",
                       "30018", "Rx", "FD,BRS", "DLC", "32", "00 00 C4 FB 0F FE 0F FE 00 00 C4 FB 0F FE 0F FE 00 00 C4 FB", None)
        self.tracetable.traces.append(newmsg)

        newmsg2 = Trace("17F00100h", "MSG",
                        "30111", "TX", "FD", "DLC", "8", "00 00 C4 FB", None)
        self.tracetable.traces.append(newmsg2)
