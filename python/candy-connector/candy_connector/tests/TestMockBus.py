from candy_connector.CanDBus import CannedBus
import candy_connector.proto.can_d_pb2 as pb


bus = CannedBus(log_path="./data/can_trace_255.log.test")

while True:
    data = bus.recv()
    print(f"Got message: {data}")
