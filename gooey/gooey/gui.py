import sys
import BreezeStyleSheets.breeze_resources
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout
from PyQt5.QtCore import QFile, QTextStream
from ui.widgets.mainwindow import CAND_MainWindow
from ui.widgets.Expander import Expander


class CAND(QMainWindow):
    def __init__(self):
        super().__init__()

        self.title = 'CAN-D Automotive Datalogger'

    def initializeUI(self):
        self.setWindowTitle(self.title)

        CAND_MainWindow(self)

        # self.layout = QVBoxLayout()
        # self.layout2 = QVBoxLayout()
        # # Test
        # self.setLayout(self.layout2)

        # self.expander = Expander()
        # self.expander.setContentLayout(self.layout2)
        # self.layout.addWidget(self.expander)
        # self.setLayout(self.layout)

        self.showMaximized()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    # set stylesheet
    file = QFile("BreezeStyleSheets/dark.qss")
    file.open(QFile.ReadOnly | QFile.Text)
    stream = QTextStream(file)
    app.setStyleSheet(stream.readAll())

    cand = CAND()
    cand.initializeUI()

    sys.exit(app.exec_())
