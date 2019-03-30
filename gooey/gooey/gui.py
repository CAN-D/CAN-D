import sys
import argparse
import stylesheet.breeze_resources
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout
from PyQt5.QtCore import QFile, QTextStream
from ui.widgets.mainwindow import CAND_MainWindow

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="CAN-D Graphical User Interface GUI")

    parser.add_argument('-d', '--is-demo', action='store_true',
                        help='connect GUI to a CAN trace?')

    parser.add_argument('-t', '--trace-location',
                        help='location of the trace file in your directory')

    args = parser.parse_args()

    app = QApplication(sys.argv)

    # set stylesheet
    file = QFile("stylesheet/dark.qss")
    file.open(QFile.ReadOnly | QFile.Text)
    stream = QTextStream(file)
    app.setStyleSheet(stream.readAll())

    cand = CAND_MainWindow(args.is_demo, args.trace_location)
    cand.showMaximized()

    sys.exit(app.exec_())
