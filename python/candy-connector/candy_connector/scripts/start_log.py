from candy_connector.CanDBus import CanDBus


def send_start_log():
    bus = CanDBus()
    bus.start_log()
    bus.stop_usb_polling()


if __name__ == "__main__":
    send_start_log()
