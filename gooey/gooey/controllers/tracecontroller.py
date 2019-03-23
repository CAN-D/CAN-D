from models.trace_table_model import TraceTableModel
from models.trace import Trace


class TraceController():
    def __init__(self, tracetable=None):
        if tracetable is not None:
            self.tracetable = tracetable
        else:
            self.tracetable = TraceTableModel()

    def setTest(self):
        newmsg = Trace(
            "30018", "18F00200h", "Rx", "FD,BRS", "32", "00 00 C4 FB 0F FE 0F FE 00 00 C4 FB 0F FE 0F FE 00 00 C4 FB")
        self.tracetable.traces.append(newmsg)

        newmsg2 = Trace(
            "30111", "17F00100h", "Tx", "FD", "8", "00 00 C4 FB")
        self.tracetable.traces.append(newmsg2)
