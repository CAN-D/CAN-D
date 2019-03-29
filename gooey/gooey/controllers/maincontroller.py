from candy_connector.CanDBus import CanDBus
from usb.core import NoBackendError

from controllers.tracecontroller import TraceController
from controllers.rxtxcontroller import RxtxController
from controllers.gpscontroller import GpsController


class MainController():
    def __init__(self, tracecontroller=None, rxtxcontroller=None, gpscontroller=None):
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

    def connect(self):
        try:
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
            print(data)

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
