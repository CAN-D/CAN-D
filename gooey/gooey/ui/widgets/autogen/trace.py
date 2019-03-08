# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui/qtdesigner/trace.ui'
#
# Created by: PyQt5 UI code generator 5.12
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_TraceTab(object):
    def setupUi(self, TraceTab):
        TraceTab.setObjectName("TraceTab")
        TraceTab.resize(1280, 778)
        self.verticalLayout = QtWidgets.QVBoxLayout(TraceTab)
        self.verticalLayout.setObjectName("verticalLayout")
        self.TraceGroup = QtWidgets.QGroupBox(TraceTab)
        self.TraceGroup.setStyleSheet("font: 18pt \".SF NS Text\";")
        self.TraceGroup.setTitle("")
        self.TraceGroup.setObjectName("TraceGroup")
        self.gridLayout = QtWidgets.QGridLayout(self.TraceGroup)
        self.gridLayout.setObjectName("gridLayout")
        self.TraceTable = QtWidgets.QTableView(self.TraceGroup)
        self.TraceTable.setObjectName("TraceTable")
        self.gridLayout.addWidget(self.TraceTable, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.TraceGroup)

        self.retranslateUi(TraceTab)
        QtCore.QMetaObject.connectSlotsByName(TraceTab)

    def retranslateUi(self, TraceTab):
        _translate = QtCore.QCoreApplication.translate
        TraceTab.setWindowTitle(_translate("TraceTab", "Form"))




if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    TraceTab = QtWidgets.QWidget()
    ui = Ui_TraceTab()
    ui.setupUi(TraceTab)
    TraceTab.show()
    sys.exit(app.exec_())
