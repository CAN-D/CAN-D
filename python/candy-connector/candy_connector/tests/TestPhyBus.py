from candy_connector.CanDBus import CanDBus
import candy_connector.proto.can_d_pb2 as pb

print("Start")
bus = CanDBus()
print("Created Bus")

while True:
    data = bus.recv()
    print(f"Read message: {data}")
