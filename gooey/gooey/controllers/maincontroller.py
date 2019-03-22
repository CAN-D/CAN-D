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
