from message import Message


class TransmitMessage(Message):
    def __init__(self, message=None, dlc=None, data=None, cycle_time=None, count=None, trigger=None):
        super().__init__(message, dlc, data, cycle_time, count)
        self.trigger = trigger
