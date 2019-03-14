from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QWidget
from models.transmit_table_model import TransmitTableModel
from models.receive_table_model import ReceiveTableModel
from models.transmit_message import TransmitMessage


class RxTxTab(QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("RxTxTab")
        self.verticalLayout = QtWidgets.QVBoxLayout(self)
        self.verticalLayout.setObjectName("verticalLayout")

        self.receiveGroup = QtWidgets.QGroupBox(self)
        self.receiveGroup.setStyleSheet("font: 18pt \".SF NS Text\";")
        self.receiveGroup.setObjectName("receiveGroup")

        self.gridLayout = QtWidgets.QGridLayout(self.receiveGroup)
        self.gridLayout.setObjectName("gridLayout")

        self.receiveTable = QtWidgets.QTableView(self.receiveGroup)
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
        self.transmitTable.setObjectName("transmitTable")
        self.transmitTable.setStyleSheet("font: 13pt;")

        self.gridLayout_2.addWidget(self.transmitTable, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.transmitGroup)

        # Set models for testing
        self.receiveTableModel = ReceiveTableModel()
        self.receiveTable.setModel(self.receiveTableModel)

        self.transmitTableModel = TransmitTableModel()
        newmsg = TransmitMessage(
            "Test1", "DLC", "Data", "cycle_time", "Count", "Trigger")
        self.transmitTableModel.messages.append(newmsg)
        self.transmitTable.setModel(self.transmitTableModel)
        newmsg2 = TransmitMessage(
            "Test2", "DLC", "Data", "cycle_time", "Count", "Trigger")
        self.transmitTableModel.messages.append(newmsg2)

        self.retranslateUi()
        QtCore.QMetaObject.connectSlotsByName(self)

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate
        self.receiveGroup.setTitle(_translate("RxTxTab", "Receive"))
        self.transmitGroup.setTitle(_translate("RxTxTab", "Transmit"))

    # TODO: REMOVE BELOW, ONLY USED FOR TESTING
    def appendTransmitTable(self, message):
        num_msgs = self.transmitTableModel.rowCount()
        self.transmitTableModel.insertRow(message, num_msgs)

    def appendReceiveTable(self, message):
        num_msgs = self.receiveTableModel.rowCount()
        self.receiveTableModel.insertRow(message, num_msgs)


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    ui = RxTxTab()
    ui.show()
    sys.exit(app.exec_())
