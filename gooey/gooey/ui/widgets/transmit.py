import time
from PyQt5 import QtCore, QtGui, QtWidgets, Qt
from PyQt5.QtWidgets import QDialog, QPushButton
from models.transmit_message import TransmitMessage


class TransmitWindow(QDialog):
    def __init__(self, parent=None, controller=None):
        super(TransmitWindow, self).__init__(parent)
        self.rxtxcontroller = controller
        self.setObjectName("Dialog")
        self.resize(300, 180)
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
        self.idInput.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.idInput.setTabChangesFocus(True)
        self.idInput.setStyleSheet("font: 12pt;")
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
        self.lengthInput.setStyleSheet("font: 12pt;")
        self.lengthInput.setObjectName("lengthInput")
        self.lengthInput.setMinimum(0)
        self.lengthInput.setMaximum(8)
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
        self.cycleInput.setStyleSheet("font: 12pt;")
        self.cycleInput.setVerticalScrollBarPolicy(
            QtCore.Qt.ScrollBarAlwaysOff)
        self.cycleInput.setHorizontalScrollBarPolicy(
            QtCore.Qt.ScrollBarAlwaysOff)
        self.cycleInput.setTabChangesFocus(True)
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
        self.dataInput.setHorizontalScrollBarPolicy(
            QtCore.Qt.ScrollBarAlwaysOff)
        self.dataInput.setTabChangesFocus(True)
        self.dataInput.setLineWrapMode(QtWidgets.QTextEdit.NoWrap)
        self.dataInput.setStyleSheet("font: 12pt;")
        self.dataForm.setWidget(
            1, QtWidgets.QFormLayout.LabelRole, self.dataInput)
        self.dataLabel = QtWidgets.QLabel(self)
        self.dataLabel.setAlignment(
            QtCore.Qt.AlignLeading | QtCore.Qt.AlignLeft | QtCore.Qt.AlignVCenter)
        self.dataLabel.setObjectName("dataLabel")
        self.dataForm.setWidget(
            0, QtWidgets.QFormLayout.LabelRole, self.dataLabel)
        self.verticalLayout.addLayout(self.dataForm)

        # Button Box
        self.buttonBox = QtWidgets.QDialogButtonBox(self)
        self.buttonBox.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setObjectName("buttonBox")
        self.verticalLayout.addWidget(self.buttonBox)

        self.sendButton = self.buttonBox.addButton(
            "Send", QtWidgets.QDialogButtonBox.AcceptRole)
        self.cancelButton = self.buttonBox.addButton(
            "Cancel", QtWidgets.QDialogButtonBox.RejectRole)
        self.clearButton = self.buttonBox.addButton(
            "Clear", QtWidgets.QDialogButtonBox.ResetRole)

        self.retranslateUi()
        self.buttonBox.accepted.connect(self.sendmessage)
        self.buttonBox.rejected.connect(self.canceled)
        self.buttonBox.buttons()[2].clicked.connect(self.cleared)

        QtCore.QMetaObject.connectSlotsByName(self)
        self.message = TransmitMessage()

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate
        self.setWindowTitle(_translate("Dialog", "Transmit Message"))
        self.windowLabel.setText(_translate("Dialog", "Transmit Message"))
        self.idLabel.setText(_translate("Dialog", "ID: (hex)"))
        self.lengthLabel.setText(_translate("Dialog", "Length:"))
        self.cycleLabel.setText(_translate("Dialog", "Cycle"))
        self.msLabel.setText(_translate("Dialog", "ms"))
        self.dataLabel.setText(_translate("Dialog", "Data: (hex)"))

    def sendmessage(self):
        self.message.parentItem = self.rxtxcontroller.transmittable.rootItem
        self.message.can_id = self.idInput.toPlainText()
        self.message.data = self.dataInput.toPlainText()
        self.message.dlc = self.lengthInput.value()
        self.message.cycle_time = self.cycleInput.toPlainText()
        self.message.time = int(round(time.time() * 1000))
        self.message.rxtx = "TX"
        self.message.count = 1
        self.accept()

    def canceled(self):
        self.reject()

    def cleared(self):
        self.dataInput.clear()
        self.lengthInput.clear()
        self.idInput.clear()
        self.cycleInput.clear()


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    ui = TransmitWindow()
    ui.show()
    sys.exit(app.exec_())
