from candy_connector.CanDBus import CanDBus
import candy_connector.proto.can_d_pb2 as pb
from candy_connector.parsers import parse_line
import logging
from can import Message


bus = CanDBus()

with open("./data/can_trace_256.log.test", "r") as log_file:
    print("Starting Loopback test...")
    print("Sending Messages")
    for log_line in log_file.readlines():
        frame_id, payload = parse_line(log_line)
        tx_msg = Message()
        tx_msg.arbitration_id = frame_id
        tx_msg.dlc = len(payload)
        tx_msg.data = bytes(payload)
        print(f"Send {tx_msg}")
        bus.send(tx_msg)
        rx_msg = bus.recv()
        assert (
            rx_msg.arbitration_id == tx_msg.arbitration_id
        ), f"Id did not match. Sent: {tx_msg.arbitration_id}, got:{rx_msg.arbitration_id}"
        assert (
            rx_msg.data == tx_msg.data
        ), f"Data did not match. Sent: {tx_msg.data}, got:{rx_msg.data}"
    print("All messages sent.")
    print("Done Loopback test")

bus.stop_usb_polling()

