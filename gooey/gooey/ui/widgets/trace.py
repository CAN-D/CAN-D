from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QWidget


class TraceTab(QWidget):
    def __init__(self, controller):
        super().__init__()
        self.controller = controller
        self.controller.setTest()

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

        self.TraceTable.setModel(self.controller.tracetable)
        self.controller.tracetable.rowsInserted.connect(
            self.scrollTraceToBottom)

        self.retranslateUi()
        QtCore.QMetaObject.connectSlotsByName(self)

    def scrollTraceToBottom(self, parent, start, end):
        QtCore.QTimer.singleShot(0, self.TraceTable.scrollToBottom)

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate
