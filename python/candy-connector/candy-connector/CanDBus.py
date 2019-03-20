"""

"""

import usb.core
from can import BusABC


class CanDBus(BusABC):
    """
    """

    def __init__(self, channel=None, can_filters=None, **config):
        """
        :param channel:
            The Serial Number of the CAN-D device

        :param list can_filters:
            A list of dictionaries each containing a "can_id", a "can_mask",
            and an "extended" key.

            >>> [{"can_id": 0x11, "can_mask": 0x21, "extended": False}]

            A filter matches, when ``<received_can_id> & can_mask == can_id & can_mask``

        :param dict config:
            Any backend dependent configurations are passed in this dictionary
        """
        super(CanDBus, self).__init__()
        self.usb_dev = usb.core.find(iSerialNumber=channel)
        if self.usb_dev is None:
            raise ValueError("CAN-D device not found")

    def recv(self, timeout=None):
        """Block waiting for a message from the Bus.

        :param float timeout: Seconds to wait for a message.

        :return:
            None on timeout or a :class:`can.Message` object.
        """

    def send(self, msg, timeout=None):
        """Transmit a message to CAN bus.
        Override this method to enable the transmit path.

        :param can.Message msg: A message object.
        :param float timeout:
            If > 0, wait up to this many seconds for message to be ACK:ed or
            for transmit queue to be ready depending on driver implementation.
            If timeout is exceeded, an exception will be raised.
            Might not be supported by all interfaces.

        :raise: :class:`can.CanError`
            if the message could not be written.
        """

    def set_filters(self, can_filters=None):
        """Apply filtering to all messages received by this Bus.

        Calling without passing any filters will reset the applied filters.

        :param list can_filters:
            A list of dictionaries each containing a "can_id" and a "can_mask".

            >>> [{"can_id": 0x11, "can_mask": 0x21}]

            A filter matches, when ``<received_can_id> & can_mask == can_id & can_mask``

        """

    def flush_tx_buffer(self):
        """Discard every message that may be queued in the output buffer(s).
        """
        pass
