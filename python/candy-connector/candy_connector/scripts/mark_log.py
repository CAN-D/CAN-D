from candy_connector.CanDBus import CanDBus

bus = CanDBus()
bus.mark_log()
bus.stop_usb_polling()
