import usb.core
import usb.util

# find our device
devs = usb.core.find(find_all=True)

for dev in devs:
    print(dev)
