from candy_connector.CanDBus import CanDBus

bus = CanDBus()
bus.start_log()
bus.stop_usb_polling()
