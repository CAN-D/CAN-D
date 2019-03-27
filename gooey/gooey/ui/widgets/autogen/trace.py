# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'qtdesigner/trace.ui'
#
# Created by: PyQt5 UI code generator 5.12.1
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
        font = QtGui.QFont()
        font.setFamily(".SF NS Text")
        font.setPointSize(18)
        font.setBold(False)
        font.setItalic(False)
        font.setWeight(50)
        self.TraceGroup.setFont(font)
        self.TraceGroup.setStyleSheet("font: 18pt \".SF NS Text\";")
        self.TraceGroup.setTitle("")
        self.TraceGroup.setObjectName("TraceGroup")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.TraceGroup)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.groupBox = QtWidgets.QGroupBox(self.TraceGroup)
        font = QtGui.QFont()
        font.setFamily(".SF NS Text")
        font.setPointSize(18)
        font.setBold(False)
        font.setItalic(False)
        font.setWeight(50)
        self.groupBox.setFont(font)
        self.groupBox.setObjectName("groupBox")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.groupBox)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.CanIDLabel = QtWidgets.QLabel(self.groupBox)
        self.CanIDLabel.setObjectName("CanIDLabel")
        self.horizontalLayout.addWidget(self.CanIDLabel, 0, QtCore.Qt.AlignVCenter)
        self.maskLineEdit = QtWidgets.QLineEdit(self.groupBox)
        self.maskLineEdit.setMaximumSize(QtCore.QSize(100, 16777215))
        self.maskLineEdit.setObjectName("maskLineEdit")
        self.horizontalLayout.addWidget(self.maskLineEdit)
        self.maskLabel = QtWidgets.QLabel(self.groupBox)
        self.maskLabel.setObjectName("maskLabel")
        self.horizontalLayout.addWidget(self.maskLabel)
        self.CanIDLineEdit = QtWidgets.QLineEdit(self.groupBox)
        self.CanIDLineEdit.setMaximumSize(QtCore.QSize(100, 16777215))
        self.CanIDLineEdit.setObjectName("CanIDLineEdit")
        self.horizontalLayout.addWidget(self.CanIDLineEdit)
        self.setButton = QtWidgets.QPushButton(self.groupBox)
        self.setButton.setMaximumSize(QtCore.QSize(48, 48))
        self.setButton.setText("")
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icons/check_circle.svg"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.setButton.setIcon(icon)
        self.setButton.setIconSize(QtCore.QSize(24, 24))
        self.setButton.setObjectName("setButton")
        self.horizontalLayout.addWidget(self.setButton, 0, QtCore.Qt.AlignTop)
        self.resetButton = QtWidgets.QPushButton(self.groupBox)
        self.resetButton.setMaximumSize(QtCore.QSize(48, 48))
        self.resetButton.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/icons/replay.svg"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.resetButton.setIcon(icon1)
        self.resetButton.setIconSize(QtCore.QSize(24, 24))
        self.resetButton.setObjectName("resetButton")
        self.horizontalLayout.addWidget(self.resetButton)
        self.verticalLayout_2.addWidget(self.groupBox, 0, QtCore.Qt.AlignLeft|QtCore.Qt.AlignTop)
        self.TraceTable = QtWidgets.QTableView(self.TraceGroup)
        self.TraceTable.setObjectName("TraceTable")
        self.verticalLayout_2.addWidget(self.TraceTable)
        self.verticalLayout.addWidget(self.TraceGroup)

        self.retranslateUi(TraceTab)
        QtCore.QMetaObject.connectSlotsByName(TraceTab)

    def retranslateUi(self, TraceTab):
        _translate = QtCore.QCoreApplication.translate
        TraceTab.setWindowTitle(_translate("TraceTab", "Form"))
        self.groupBox.setTitle(_translate("TraceTab", "Filter Message"))
        self.CanIDLabel.setText(_translate("TraceTab", "CAN ID"))
        self.maskLabel.setText(_translate("TraceTab", "Mask"))


from widgets import resources_rc


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    TraceTab = QtWidgets.QWidget()
    ui = Ui_TraceTab()
    ui.setupUi(TraceTab)
    TraceTab.show()
    sys.exit(app.exec_())
