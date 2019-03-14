import sys
import stylesheet.breeze_resources
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout
from PyQt5.QtCore import QFile, QTextStream
from ui.widgets.mainwindow import CAND_MainWindow
from ui.widgets.Expander import Expander

if __name__ == "__main__":
    app = QApplication(sys.argv)

    # set stylesheet
    file = QFile("stylesheet/dark.qss")
    file.open(QFile.ReadOnly | QFile.Text)
    stream = QTextStream(file)
    app.setStyleSheet(stream.readAll())

    cand = CAND_MainWindow()
    cand.showMaximized()

    sys.exit(app.exec_())
