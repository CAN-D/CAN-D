from candy_connector.CanDBus import CanDBus

bus = CanDBus()

while True:
    print(bus.recv())
