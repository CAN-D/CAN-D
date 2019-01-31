import sys
import random
from PySide2 import QtCore, QtWidgets, QtGui

class CAND(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.title = 'CAN-D Automotive Datalogger'
        self.hello = ["Hallo Welt", "Hei maailma", "Hola Mundo", "Привет мир"]
        self.initializeUI()

    def initializeUI(self):
        self.setWindowTitle(self.title)
        self.button = QtWidgets.QPushButton("Click me!")
        self.text = QtWidgets.QLabel("Hello World")
        self.text.setAlignment(QtCore.Qt.AlignCenter)

        self.layout = QtWidgets.QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)
        self.setLayout(self.layout)

        self.button.clicked.connect(self.magic)
        
        self.showMaximized()

    def magic(self):
        text = random.choice(self.hello)
        self.text.setText(text)
        self.text.repaint()


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)

    cand = CAND()

    sys.exit(app.exec_())