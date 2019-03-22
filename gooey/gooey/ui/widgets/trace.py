from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QWidget
from models.trace_table_model import TraceTableModel
from models.trace import Trace


class TraceTab(QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("TraceTab")
        self.resize(1280, 778)
        self.verticalLayout = QtWidgets.QVBoxLayout(self)
        self.verticalLayout.setObjectName("verticalLayout")
        self.TraceGroup = QtWidgets.QGroupBox(self)
        self.TraceGroup.setStyleSheet("font: 13pt \".SF NS Text\";")
        self.TraceGroup.setTitle("")
        self.TraceGroup.setObjectName("TraceGroup")
        self.gridLayout = QtWidgets.QGridLayout(self.TraceGroup)
        self.gridLayout.setObjectName("gridLayout")
        self.TraceTable = QtWidgets.QTableView(self.TraceGroup)
        self.TraceTable.setObjectName("TraceTable")
        self.TraceTable.setEditTriggers(
            QtWidgets.QAbstractItemView.NoEditTriggers)
        self.gridLayout.addWidget(self.TraceTable, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.TraceGroup)

        header = self.TraceTable.horizontalHeader()
        header.setStretchLastSection(True)

        self.traceTableModel = TraceTableModel()
        newmsg = Trace(
            "30018", "18F00200h", "Rx", "FD,BRS", "32", "00 00 C4 FB 0F FE 0F FE 00 00 C4 FB 0F FE 0F FE 00 00 C4 FB")
        self.traceTableModel.traces.append(newmsg)
        self.TraceTable.setModel(self.traceTableModel)
        newmsg2 = Trace(
            "30111", "17F00100h", "Tx", "FD", "8", "00 00 C4 FB")
        self.traceTableModel.traces.append(newmsg2)

        self.retranslateUi()
        QtCore.QMetaObject.connectSlotsByName(self)

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    tab = QtWidgets.QWidget()
    ui = TraceTab()
    ui.show()
    sys.exit(app.exec_())
