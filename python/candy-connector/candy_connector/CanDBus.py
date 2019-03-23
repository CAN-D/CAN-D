"""

"""
# Builtin Python
import asyncio
import logging
from queue import Queue
from typing import List, Dict, Optional

# External Python
import usb.core
import usb.util
from can import BusABC, Message
from google.protobuf.message import DecodeError

# Package Python
import candy_connector.proto.can_d_pb2 as pb


class CanDBus(BusABC):
    """
    Bus API:
        send
        recv
        set_filters
        flush_tx_buffer
    Additional API:
        send_command
    """

    def __init__(
        self, channel: int = None, can_filters: Dict[str, int] = None, **config
    ):
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
        super(CanDBus, self).__init__(channel=channel)
        # Init data structures
        self.can_queue = asyncio.Queue()
        self.gps_queue = asyncio.Queue()
        self.most_recent_fs_info = []

        # Setup the USB connection
        if channel != None:
            usb_dev = usb.core.find(iSerialNumber=channel, manufacturer="CAN-D")
        else:
            usb_dev = usb.core.find(manufacturer="CAN-D")

        if usb_dev is None:
            raise ValueError("CAN-D device not found")

        usb_dev.set_configuration()
        cfg = usb_dev.get_active_configuration()
        intf = cfg[(1, 0)]

        self.usb_endpoint_out = usb.util.find_descriptor(
            intf,
            custom_match=lambda e: usb.util.endpoint_direction(e.bEndpointAddress)
            == usb.util.ENDPOINT_OUT,
        )

        self.usb_endpoint_in = usb.util.find_descriptor(
            intf,
            custom_match=lambda e: usb.util.endpoint_direction(e.bEndpointAddress)
            == usb.util.ENDPOINT_IN,
        )

        if self.usb_endpoint_in is None:
            raise ValueError(
                "Could not establish an outgoing endpoint for the CAN-D device."
            )
        if self.usb_endpoint_out is None:
            raise ValueError(
                "Could not establish an incoming endpoint for the CAN-D device."
            )

        # Start polling from the USB
        asyncio.run(self._async_poll_usb())

    def recv(self, timeout: float = None) -> Optional[Message]:
        """Block waiting for a message from the Bus.

        :param float timeout: Seconds to wait for a message.

        :return:
            None on timeout or a :class:`can.Message` object.
        """
        return self.can_queue.get(block=True)

    def send(self, msg: Message, timeout=None):
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

    def set_filters(self, can_filters: Dict[str, int] = None):
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

    async def _async_poll_usb(self):
        """Asyncronously poll the usb device for data forever."""
        while True:
            in_bytes = await self._read_usb()
            print(f"Got bytes: {in_bytes}")
            self._handle_raw(in_bytes)

    async def _read_usb(self, max_len: int = 100) -> bytes:
        """Asynchronously read from the usb device."""
        try:
            return bytes(self.usb_endpoint_in.read(max_len))
        except usb.core.USBError:
            logging.warning("Unable to read from the USB.")
            return bytes()

    def _handle_raw(self, raw_bytes: bytes):
        """Interpret incoming raw protobuf data."""
        try:
            from_embedded = pb.FromEmbedded()
            from_embedded.ParseFromString(raw_bytes)
            if from_embedded.HasField("canDataChunk"):
                self._handle_can_data(from_embedded.canDataChunk)
            if from_embedded.HasField("gpsDataChunk"):
                self._handle_gps_data(from_embedded.gpsDataChunk)
            if from_embedded.HasField("logFSInfo"):
                self._handle_fs_info(from_embedded.logFSInfo)
        except DecodeError:
            logging.warning("Unable to decode bytes: %s", raw_bytes)

    def _handle_can_data(self, can_data: pb.DataPayload):
        """Handle incoming CAN data."""
        self.can_queue.put_nowait(Message(data=can_data.data))

    def _handle_gps_data(self, gps_data: pb.DataPayload):
        """Handle incoming GPS data."""
        self.gps_queue.put_nowait(gps_data.data)

    def _handle_fs_info(self, fs_info_list: pb.LogFSInfo):
        """Handle incoming information about the embedded file system."""
        # TODO: Probably dont need to actually store this. Should pass to a listener
        self.fs_info = fs_info_list

