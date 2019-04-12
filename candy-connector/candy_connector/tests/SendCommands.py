import usb.core
import usb.util
from time import sleep
from candy_connector.CanDBus import CanDBus

bus = CanDBus()
bus.start_log()
bus.stop_usb_polling()

while True:
    print("Sleep for 10s... ...zzz.")
    sleep(10)
    print("Send Stop Command.")
    bus.stop_log()
