# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'qtdesigner/rxtx.ui'
#
# Created by: PyQt5 UI code generator 5.12
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class RxTxTab(object):
    def __init__(self, RxTxTab):
        RxTxTab.setObjectName("RxTxTab")
        self.verticalLayout = QtWidgets.QVBoxLayout(RxTxTab)
        self.verticalLayout.setObjectName("verticalLayout")

        self.receiveGroup = QtWidgets.QGroupBox(RxTxTab)
        self.receiveGroup.setStyleSheet("font: 18pt \".SF NS Text\";")
        self.receiveGroup.setObjectName("receiveGroup")

        self.gridLayout = QtWidgets.QGridLayout(self.receiveGroup)
        self.gridLayout.setObjectName("gridLayout")

        self.receiveTable = QtWidgets.QTableView(self.receiveGroup)
        self.receiveTable.setObjectName("receiveTable")
        self.receiveTable.setStyleSheet("font: 13pt;")

        self.gridLayout.addWidget(self.receiveTable, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.receiveGroup)

        self.transmitGroup = QtWidgets.QGroupBox(RxTxTab)
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
        receiveModel = QtGui.QStandardItemModel()
        receiveModel.setHorizontalHeaderLabels(
            ['Message', 'DLC', 'Data', 'Cycle Time', 'Count'])
        self.receiveTable.setModel(receiveModel)

        transmitModel = QtGui.QStandardItemModel()
        transmitModel.setHorizontalHeaderLabels(
            ['Message', 'DLC', 'Data', 'Cycle Time', 'Count', 'Trigger'])
        self.transmitTable.setModel(transmitModel)

        self.retranslateUi(RxTxTab)
        QtCore.QMetaObject.connectSlotsByName(RxTxTab)

    def retranslateUi(self, RxTxTab):
        _translate = QtCore.QCoreApplication.translate
        self.receiveGroup.setTitle(_translate("RxTxTab", "Receive"))
        self.transmitGroup.setTitle(_translate("RxTxTab", "Transmit"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    rxtx = QtWidgets.QWidget()
    ui = RxTxTab(rxtx)
    rxtx.show()
    sys.exit(app.exec_())
