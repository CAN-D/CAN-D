from candy_connector.CanDBus import CanDBus
import candy_connector.proto.can_d_pb2 as pb


bus = CanDBus()

while True:
    data = bus.recv()
    print(f"Read raw: {data}")
    try:
        from_embedded = pb.FromEmbedded()
        from_embedded.ParseFromString(data)
        print(f"Decode: {from_embedded}")
    except:
        print("Unable to decode.")
