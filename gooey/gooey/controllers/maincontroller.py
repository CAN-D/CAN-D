from candy_connector.CanDBus import CanDBus
from candy_connector.CanDBus import CannedBus

from usb.core import NoBackendError

from controllers.tracecontroller import TraceController
from controllers.rxtxcontroller import RxtxController
from controllers.gpscontroller import GpsController
from PyQt5 import QtCore


class MainController():
    def __init__(self, isdemo, trace_location, tracecontroller=None, rxtxcontroller=None, gpscontroller=None):
        self.isdemo = isdemo
        self.trace_location = trace_location

        if tracecontroller is not None:
            self.tracecontroller = tracecontroller
        else:
            self.tracecontroller = TraceController()

        if rxtxcontroller is not None:
            self.rxtxcontroller = rxtxcontroller
        else:
            self.rxtxcontroller = RxtxController()

        if gpscontroller is not None:
            self.gpscontroller = gpscontroller
        else:
            self.gpscontroller = GpsController()

        self.polling = False
        self.connected = False
        self.candbus = None
        self.logging = False
        self.dbc = None

    def connect(self):
        try:
            if self.isdemo:
                self.candbus = CannedBus(log_path=self.trace_location)
            else:
                self.candbus = CanDBus()

            self.connected = True

        except NoBackendError:
            print("No hardware")

        return self.connected

    def disconnect(self):
        self.connected = False
        self.candbus.stop_usb_polling()
        self.candbus.stop_log()
        self.candbus = None
        self.polling = False
        self.logging = False

        return self.connected

    def startPoll(self):
        self.polling = True

        while self.polling and self.connected:
            data = self.candbus.recv()
            print(f"Got message: {data}")

    def startLog(self):
        if self.candbus is not None:
            self.logging = True
            self.candbus.start_log()

        return self.logging

    def stopLog(self):
        if self.candbus is not None:
            self.logging = False
            self.candbus.stop_log()

        return self.logging

    def markLog(self):
        # TODO
        return


class DataPollThread(QtCore.QThread):
    data_incoming = QtCore.pyqtSignal(object)

    def __init__(self, bus):
        QtCore.QThread.__init__(self)
        self.polling = False
        self.candbus = bus

    def run(self):
        self.polling = True

        while self.polling:
            data = self.candbus.recv()
            self.data_incoming.emit(data)
