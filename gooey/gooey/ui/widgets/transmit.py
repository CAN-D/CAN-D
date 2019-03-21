from PyQt5 import QtCore, QtGui, QtWidgets, Qt
from PyQt5.QtWidgets import QDialog


class TransmitWindow(QDialog):
    def __init__(self, parent=None):
        super(TransmitWindow, self).__init__(parent)
        self.setObjectName("Dialog")
        self.resize(350, 330)
        self.verticalLayout = QtWidgets.QVBoxLayout(self)
        self.verticalLayout.setObjectName("verticalLayout")
        self.windowLabel = QtWidgets.QLabel(self)
        font = QtGui.QFont()
        font.setPointSize(18)
        self.windowLabel.setFont(font)
        self.windowLabel.setObjectName("windowLabel")
        self.verticalLayout.addWidget(self.windowLabel)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")

        # ID Input
        self.idForm = QtWidgets.QFormLayout()
        self.idForm.setObjectName("idForm")
        self.idInput = QtWidgets.QTextEdit(self)
        self.idInput.setMaximumSize(QtCore.QSize(100, 25))
        self.idInput.setObjectName("idInput")
        self.idInput.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.idInput.setLineWrapMode(QtWidgets.QTextEdit.NoWrap)
        self.idForm.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.idInput)

        self.idLabel = QtWidgets.QLabel(self)
        self.idLabel.setObjectName("idLabel")
        self.idForm.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.idLabel)
        self.horizontalLayout.addLayout(self.idForm)

        # Length Input
        self.lengthForm = QtWidgets.QFormLayout()
        self.lengthForm.setObjectName("lengthForm")
        self.lengthInput = QtWidgets.QSpinBox(self)
        self.lengthInput.setMinimumSize(QtCore.QSize(45, 0))
        self.lengthInput.setObjectName("lengthInput")
        self.lengthForm.setWidget(
            1, QtWidgets.QFormLayout.LabelRole, self.lengthInput)

        self.lengthLabel = QtWidgets.QLabel(self)
        self.lengthLabel.setObjectName("lengthLabel")
        self.lengthForm.setWidget(
            0, QtWidgets.QFormLayout.LabelRole, self.lengthLabel)
        self.horizontalLayout.addLayout(self.lengthForm)

        # Cycle Input
        self.cycleForm = QtWidgets.QFormLayout()
        self.cycleForm.setObjectName("cycleForm")
        self.cycleInput = QtWidgets.QTextEdit(self)
        self.cycleInput.setMaximumSize(QtCore.QSize(75, 25))
        self.cycleInput.setObjectName("cycleInput")
        self.cycleInput.setVerticalScrollBarPolicy(
            QtCore.Qt.ScrollBarAlwaysOff)
        self.cycleInput.setLineWrapMode(QtWidgets.QTextEdit.NoWrap)
        self.cycleForm.setWidget(
            1, QtWidgets.QFormLayout.LabelRole, self.cycleInput)

        # Cycle Label
        self.cycleLabel = QtWidgets.QLabel(self)
        self.cycleLabel.setObjectName("cycleLabel")
        self.cycleForm.setWidget(
            0, QtWidgets.QFormLayout.LabelRole, self.cycleLabel)

        self.msLabel = QtWidgets.QLabel(self)
        self.msLabel.setObjectName("msLabel")
        self.cycleForm.setWidget(
            1, QtWidgets.QFormLayout.FieldRole, self.msLabel)
        self.horizontalLayout.addLayout(self.cycleForm)
        self.verticalLayout.addLayout(self.horizontalLayout)

        # Data input
        self.dataForm = QtWidgets.QFormLayout()
        self.dataForm.setObjectName("dataForm")
        self.dataInput = QtWidgets.QTextEdit(self)
        self.dataInput.setMinimumSize(QtCore.QSize(305, 0))
        self.dataInput.setMaximumSize(QtCore.QSize(16777215, 25))
        self.dataInput.setObjectName("dataInput")
        self.dataInput.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.dataInput.setLineWrapMode(QtWidgets.QTextEdit.NoWrap)
        self.dataForm.setWidget(
            1, QtWidgets.QFormLayout.LabelRole, self.dataInput)
        self.dataLabel = QtWidgets.QLabel(self)
        self.dataLabel.setAlignment(
            QtCore.Qt.AlignLeading | QtCore.Qt.AlignLeft | QtCore.Qt.AlignVCenter)
        self.dataLabel.setObjectName("dataLabel")
        self.dataForm.setWidget(
            0, QtWidgets.QFormLayout.LabelRole, self.dataLabel)
        self.verticalLayout.addLayout(self.dataForm)

        # Message Type Group Box
        self.msgTypeGroupBox = QtWidgets.QGroupBox(self)
        self.msgTypeGroupBox.setObjectName("msgTypeGroupBox")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.msgTypeGroupBox)
        self.verticalLayout_2.setObjectName("verticalLayout_2")

        # EF check box
        self.efCheckBox = QtWidgets.QCheckBox(self.msgTypeGroupBox)
        self.efCheckBox.setObjectName("efCheckBox")
        self.verticalLayout_2.addWidget(self.efCheckBox)

        # RR Check box
        self.rrCheckBox = QtWidgets.QCheckBox(self.msgTypeGroupBox)
        self.rrCheckBox.setObjectName("rrCheckBox")
        self.verticalLayout_2.addWidget(self.rrCheckBox)

        # FD Check box
        self.fdCheckBox = QtWidgets.QCheckBox(self.msgTypeGroupBox)
        self.fdCheckBox.setObjectName("fdCheckBox")
        self.verticalLayout_2.addWidget(self.fdCheckBox)

        # BRS Check box
        self.brsCheckBox = QtWidgets.QCheckBox(self.msgTypeGroupBox)
        self.brsCheckBox.setObjectName("brsCheckBox")
        self.verticalLayout_2.addWidget(self.brsCheckBox)
        self.verticalLayout.addWidget(self.msgTypeGroupBox)

        # Button Box
        self.buttonBox = QtWidgets.QDialogButtonBox(self)
        self.buttonBox.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(
            QtWidgets.QDialogButtonBox.Cancel | QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.verticalLayout.addWidget(self.buttonBox)

        self.retranslateUi()
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)
        QtCore.QMetaObject.connectSlotsByName(self)

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate
        self.setWindowTitle(_translate("Dialog", "Transmit Message"))
        self.windowLabel.setText(_translate("Dialog", "Transmit Message"))
        self.idLabel.setText(_translate("Dialog", "ID: (hex)"))
        self.lengthLabel.setText(_translate("Dialog", "Length:"))
        self.cycleLabel.setText(_translate("Dialog", "Cycle"))
        self.msLabel.setText(_translate("Dialog", "ms"))
        self.dataLabel.setText(_translate("Dialog", "Data: (hex)"))
        self.msgTypeGroupBox.setTitle(_translate("Dialog", "Message Type"))
        self.efCheckBox.setText(_translate("Dialog", "Extended Frame"))
        self.rrCheckBox.setText(_translate("Dialog", "Remote Request"))
        self.fdCheckBox.setText(_translate("Dialog", "CAN FD"))
        self.brsCheckBox.setText(_translate("Dialog", "Bit Rate Switch (BRS)"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    ui = TransmitWindow()
    ui.show()
    sys.exit(app.exec_())
