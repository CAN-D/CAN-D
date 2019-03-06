from PyQt5 import QtCore, QtGui, QtWidgets


class TraceTab(object):
    def __init__(self, TraceTab):
        TraceTab.setObjectName("TraceTab")
        TraceTab.resize(1280, 778)
        self.verticalLayout = QtWidgets.QVBoxLayout(TraceTab)
        self.verticalLayout.setObjectName("verticalLayout")
        self.TraceGroup = QtWidgets.QGroupBox(TraceTab)
        self.TraceGroup.setStyleSheet("font: 13pt \".SF NS Text\";")
        self.TraceGroup.setTitle("")
        self.TraceGroup.setObjectName("TraceGroup")
        self.gridLayout = QtWidgets.QGridLayout(self.TraceGroup)
        self.gridLayout.setObjectName("gridLayout")
        self.TraceTable = QtWidgets.QTableView(self.TraceGroup)
        self.TraceTable.setObjectName("TraceTable")
        self.gridLayout.addWidget(self.TraceTable, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.TraceGroup)

        # Set models for testing
        traceModel = QtGui.QStandardItemModel()
        traceModel.setHorizontalHeaderLabels(
            ['Time', 'CAN-ID', 'Rx/Tx', 'Type', 'Length', 'Data'])
        self.TraceTable.setModel(traceModel)

        self.retranslateUi(TraceTab)
        QtCore.QMetaObject.connectSlotsByName(TraceTab)

    def retranslateUi(self, TraceTab):
        _translate = QtCore.QCoreApplication.translate


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    tab = QtWidgets.QWidget()
    ui = TraceTab(tab)
    tab.show()
    sys.exit(app.exec_())
