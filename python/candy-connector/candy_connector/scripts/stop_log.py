from candy_connector.CanDBus import CanDBus


def send_stop_command():
    bus = CanDBus()
    bus.stop_log()
    bus.stop_usb_polling()


if __name__ == "__main__":
    send_stop_command()
