"""

"""
# Builtin Python
import asyncio
from queue import Queue
from typing import List, Queue

# External Python
import usb.core
import usb.util
from can import BusABC, Message

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
        self, channel: int = None, can_filters: List[str:int] = None, **config
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
        super(CanDBus, self).__init__()
        # Init data structures
        self.can_queue: Queue[Message] = Queue()
        self.gps_queue: Queue[bytes] = Queue()
        self.most_recent_fs_info: pb.LogFSInfo = []

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
        # # write the data
        # usb_endpoint_out.write("test")
        # # read some data
        # while True:
        #     print(bytes(usb_endpoint_in.read(18)))

        # Start polling from the USB
        asyncio.run(self._poll_usb())

    def recv(self, timeout=None):
        """Block waiting for a message from the Bus.

        :param float timeout: Seconds to wait for a message.

        :return:
            None on timeout or a :class:`can.Message` object.
        """
        return self.can_queue.get(block=True)

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

    async def _poll_usb(self):
        """Asyncronously poll the usb device for data forever."""
        while True:
            in_bytes = await self._read_usb()
            self._handle_raw(in_bytes)

    async def _read_usb(self) -> bytes:
        """Asynchronously read from the usb device."""
        message_len = self.usb_endpoint_in.read(2)
        return bytes(self.usb_endpoint_in.read(message_len, 2))

    def _handle_raw(self, raw_bytes: bytes):
        """Interpret incoming raw protobuf data."""
        from_embedded = pb.FromEmbedded()
        from_embedded.ParseFromString(raw_bytes)

        if from_embedded.HasField("canDataChunk"):
            self._handle_can_data(from_embedded.canDataChunk)
        if from_embedded.HasField("gpsDataChunk"):
            self._handle_gps_data(from_embedded.gpsDataChunk)
        if from_embedded.HasField("logFSInfo"):
            self._handle_fs_info(from_embedded.logFSInfo)

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

