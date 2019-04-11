from models.trace_table_model import TraceTableModel
from models.trace import Trace

class TraceController():
    """ The controller which holds data for the Trace tab.

        :param `tracetable`: An array containing Trace objects.
        :param `can_id`: The CAN ID that is used as a filter.
        :param `can_mask`: A Mask used to filter traces coming in from the device
        :param `dbcpath`: The path of the DBC file to be applied.
    """
    def __init__(self, tracetable=None, can_id=None, can_mask=None, dbcpath=None):
        if tracetable is not None:
            self.tracetable = tracetable
        else:
            self.tracetable = TraceTableModel()

        self.can_id = can_id
        self.can_mask = can_mask
        self.dbcpath = dbcpath

    def appendTraceTable(self, message):
        """ Appends to the trace table.
        
        Arguments:
            message {Trace} -- A Trace object, containing raw data from the CAN-D device.
        """
        self.tracetable.insertRow(message)
