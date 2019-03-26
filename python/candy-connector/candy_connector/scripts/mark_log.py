from candy_connector.CanDBus import CanDBus


def send_mark_log():
    bus = CanDBus()
    bus.mark_log()
    bus.stop_usb_polling()


if __name__ == "__main__":
    send_mark_command()
