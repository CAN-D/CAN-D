from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QWidget


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
        self.gridLayout.addWidget(self.TraceTable, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.TraceGroup)
        self.TraceTable.setEditTriggers(
            QtWidgets.QAbstractItemView.NoEditTriggers)

        # Set models for testing
        traceModel = QtGui.QStandardItemModel()
        traceModel.setHorizontalHeaderLabels(
            ['Time', 'CAN-ID', 'Rx/Tx', 'Type', 'Length', 'Data'])
        self.TraceTable.setModel(traceModel)

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
