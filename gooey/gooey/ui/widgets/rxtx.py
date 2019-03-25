from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QWidget
from models.transmit_message import TransmitMessage


class RxTxTab(QWidget):
    def __init__(self, controller):
        super().__init__()
        self.controller = controller
        self.controller.setTest()

        self.setObjectName("RxTxTab")
        self.verticalLayout = QtWidgets.QVBoxLayout(self)
        self.verticalLayout.setObjectName("verticalLayout")

        self.receiveGroup = QtWidgets.QGroupBox(self)
        self.receiveGroup.setStyleSheet("font: 18pt \".SF NS Text\";")
        self.receiveGroup.setObjectName("receiveGroup")

        self.gridLayout = QtWidgets.QGridLayout(self.receiveGroup)
        self.gridLayout.setObjectName("gridLayout")

        self.receiveTable = QtWidgets.QTableView(self.receiveGroup)
        self.receiveTable.setEditTriggers(
            QtWidgets.QAbstractItemView.NoEditTriggers)
        self.receiveTable.setSelectionBehavior(QtWidgets.QTableView.SelectRows)
        self.receiveTable.setObjectName("receiveTable")
        self.receiveTable.setStyleSheet("font: 13pt;")

        self.gridLayout.addWidget(self.receiveTable, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.receiveGroup)

        self.transmitGroup = QtWidgets.QGroupBox(self)
        self.transmitGroup.setStyleSheet("font: 18pt \".SF NS Text\";")
        self.transmitGroup.setObjectName("transmitGroup")

        self.gridLayout_2 = QtWidgets.QGridLayout(self.transmitGroup)
        self.gridLayout_2.setObjectName("gridLayout_2")

        self.transmitTable = QtWidgets.QTableView(self.transmitGroup)
        self.transmitTable.setEditTriggers(
            QtWidgets.QAbstractItemView.NoEditTriggers)
        self.transmitTable.setSelectionBehavior(
            QtWidgets.QTableView.SelectRows)
        self.transmitTable.setObjectName("transmitTable")
        self.transmitTable.setStyleSheet("font: 13pt;")

        self.gridLayout_2.addWidget(self.transmitTable, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.transmitGroup)

        # Set models for testing
        self.receiveTable.setModel(self.controller.receivetable)
        self.transmitTable.setModel(self.controller.transmittable)

        self.controller.transmittable.rowsInserted.connect(
            self.scrollTransmitToBottom)
        self.controller.receivetable.rowsInserted.connect(
            self.scrollReceiveToBottom)

        self.retranslateUi()
        QtCore.QMetaObject.connectSlotsByName(self)

    def scrollTransmitToBottom(self, parent, start, end):
        QtCore.QTimer.singleShot(0, self.transmitTable.scrollToBottom)

    def scrollReceiveToBottom(self, parent, start, end):
        QtCore.QTimer.singleShot(0, self.receiveTable.scrollToBottom)

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate
        self.receiveGroup.setTitle(_translate("RxTxTab", "Receive"))
        self.transmitGroup.setTitle(_translate("RxTxTab", "Transmit"))
