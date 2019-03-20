import usb.core
import usb.util

# find our device
dev = usb.core.find(manufacturer="CAN-D")

# was it found?
if dev is None:
    raise ValueError("Device not found")

# set the active configuration. With no arguments, the first
# configuration will be the active one
dev.set_configuration()

# get an endpoint instance
cfg = dev.get_active_configuration()
intf = cfg[(1, 0)]

ep_out = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match=lambda e: usb.util.endpoint_direction(e.bEndpointAddress)
    == usb.util.ENDPOINT_OUT,
)

assert ep_out is not None

ep_in = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match=lambda e: usb.util.endpoint_direction(e.bEndpointAddress)
    == usb.util.ENDPOINT_IN,
)

assert ep_in is not None

# write the data
ep_out.write("test")
# read some data
while True:
    print(bytes(ep_in.read(18)))
