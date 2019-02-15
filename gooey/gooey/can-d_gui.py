import sys
import random
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLabel, QVBoxLayout
from PyQt5.QtCore import Qt
from ui.Expander import Expander

class CAND(QWidget):
    def __init__(self):
        super().__init__()

        self.title = 'CAN-D Automotive Datalogger'
        self.hello = ["Hallo Welt", "Hei maailma", "Hola Mundo", "Привет мир"]
        self.initializeUI()

    def initializeUI(self):
        self.setWindowTitle(self.title)
        self.button = QPushButton("Click me!")
        self.text = QLabel("Hello World")
        self.text.setAlignment(Qt.AlignCenter)

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)

        self.layout2 = QVBoxLayout()
        self.layout2.addWidget(self.text)
        self.layout2.addWidget(self.button)
        self.setLayout(self.layout2)

        self.expander = Expander();
        self.expander.setContentLayout(self.layout2);
        self.layout.addWidget(self.expander)
        self.setLayout(self.layout)

        self.button.clicked.connect(self.magic)


        self.showMaximized()

    def magic(self):
        text = random.choice(self.hello)
        self.text.setText(text)
        self.text.repaint()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    cand = CAND()

    sys.exit(app.exec_())
