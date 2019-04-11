from candy_connector.CanDBus import CanDBus
from candy_connector.CanDBus import CannedBus
from candy_connector.CanDBus import LoopbackBus

from usb.core import NoBackendError

from controllers.tracecontroller import TraceController
from controllers.rxtxcontroller import RxtxController
from PyQt5 import QtCore

class MainController(object):
    """ The main controller for the whole application, contains a singleton of all the other controllers in the application.

        :param `isdemo`: a boolean, True if the program is launched for the demo; False, otherwise.
        :param `trace_location`: a path to the trace file containing the data to be shown in the demo.
        :param `tracecontroller`: A TraceController holding the data for the Trace tab.
        :param `rxtxcontroller`: A RxTxController holding the data for the Receive/Transmit tab.
    """
    def __init__(self, isdemo, isloopback, trace_location, tracecontroller=None, rxtxcontroller=None):
        self.isdemo = isdemo
        self.isloopback = isloopback
        self.trace_location = trace_location

        if tracecontroller is not None:
            self.tracecontroller = tracecontroller
        else:
            self.tracecontroller = TraceController()

        if rxtxcontroller is not None:
            self.rxtxcontroller = rxtxcontroller
        else:
            self.rxtxcontroller = RxtxController(self)

        self.polling = False
        self.connected = False
        self.candbus = None
        self.logging = False
        self.dbc = None
        self.open_file_path = ""

    def connect(self):
        """ Connects the user interface to the CAN-D hardware device.
        
            Returns:
                boolean -- True if successfully connected; False, otherwise.
        """
        try:
            if self.isdemo:
                self.candbus = CannedBus(log_path=self.trace_location)
            elif self.isloopback:
                self.candbus = LoopbackBus()
            else:
                self.candbus = CanDBus()

            self.connected = True

        except NoBackendError:
            print("No hardware")

        return self.connected

    def disconnect(self):
        """ Disconnects the user interface from the CAN-D hardware device.
        
            Returns:
                boolean -- True if successfully disconnected; False, otherwise.
        """
        self.connected = False
        self.candbus.stop_usb_polling()
        self.candbus.stop_log()
        self.candbus = None
        self.polling = False
        self.logging = False

        return self.connected

    def startLog(self):
        """ Start logging data from the CAN-D device to the SD card.
        
            Returns:
                boolean -- True if the CAN-D device has started logging.
        """

        if self.candbus is not None:
            self.logging = True
            self.candbus.start_log()

        return self.logging

    def stopLog(self):
        """ Stop logging data from the CAN-D device to the SD card.

            Returns:
                boolean -- True if the CAN-D device has stopped logging.
        """

        if self.candbus is not None:
            self.logging = False
            self.candbus.stop_log()

        return self.logging

    def markLog(self):
        """ Marks the log in the logfile that happened in the same time instance this function is called.

            Returns:
                boolean -- True if marking the log is successful. False, otherwise.
        """

        if self.candbus is not None:
            self.candbus.mark_log()
            return True

        return False


class DataPollThread(QtCore.QThread):
    """ A separate QtCore.QThread so that data can be polled from the CAN-D device on a separate thread
    and keep the UI responsive.

    :param `bus`: The CAN-D bus that the UI is connected to.    
    """

    data_incoming = QtCore.pyqtSignal(object)

    def __init__(self, bus):
        QtCore.QThread.__init__(self)
        self.polling = False
        self.candbus = bus

    def run(self):
        """ Run the poller thread.
        """
        self.polling = True

        # Receive data from the CAN bus and emit the data_incoming signal.
        while self.polling:
            data = self.candbus.recv()
            self.data_incoming.emit(data)
