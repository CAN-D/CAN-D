from message import Message


class ReceiveMessage(Message):
    def __init__(self, message=None, dlc=None, data=None, cycle_time=None, count=None):
        super().__init__(message, dlc, data, cycle_time, count)
