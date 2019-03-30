from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QWidget


class TraceTab(QWidget):
    def __init__(self, controller):
        super().__init__()
        self.controller = controller
        self.setObjectName("TraceTab")
        self.resize(1280, 778)
        self.verticalLayout = QtWidgets.QVBoxLayout(self)
        self.verticalLayout.setObjectName("verticalLayout")
        self.TraceGroup = QtWidgets.QGroupBox(self)
        self.TraceGroup.setTitle("")
        self.TraceGroup.setObjectName("TraceGroup")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.TraceGroup)
        self.verticalLayout_2.setObjectName("verticalLayout_2")

        self.groupBox = QtWidgets.QGroupBox(self.TraceGroup)
        self.groupBox.setObjectName("groupBox")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.groupBox)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.CanIDLabel = QtWidgets.QLabel(self.groupBox)
        self.CanIDLabel.setObjectName("CanIDLabel")
        self.horizontalLayout.addWidget(
            self.CanIDLabel, 0, QtCore.Qt.AlignVCenter)
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
        icon.addPixmap(QtGui.QPixmap(":/icons/check_circle.svg"),
                       QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.setButton.setIcon(icon)
        self.setButton.setIconSize(QtCore.QSize(24, 24))
        self.setButton.setObjectName("setButton")
        self.horizontalLayout.addWidget(self.setButton, 0, QtCore.Qt.AlignTop)
        self.resetButton = QtWidgets.QPushButton(self.groupBox)
        self.resetButton.setMaximumSize(QtCore.QSize(48, 48))
        self.resetButton.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/icons/replay.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.resetButton.setIcon(icon1)
        self.resetButton.setIconSize(QtCore.QSize(24, 24))
        self.resetButton.setObjectName("resetButton")
        self.horizontalLayout.addWidget(self.resetButton)
        self.verticalLayout_2.addWidget(
            self.groupBox, 0, QtCore.Qt.AlignLeft | QtCore.Qt.AlignTop)

        self.TraceTable = QtWidgets.QTableView(self.TraceGroup)
        self.TraceTable.setEditTriggers(
            QtWidgets.QAbstractItemView.NoEditTriggers)
        self.TraceTable.setObjectName("TraceTable")
        header = self.TraceTable.horizontalHeader()
        header.setStretchLastSection(True)

        self.verticalLayout_2.addWidget(self.TraceTable)
        self.verticalLayout.addWidget(self.TraceGroup)

        self.TraceTable.setModel(self.controller.tracetable)

        self.controller.tracetable.rowsInserted.connect(
            self.scrollTraceToBottom)
        self.CanIDLineEdit.textChanged.connect(self.canIdFilterChanged)
        self.maskLineEdit.textChanged.connect(self.canMaskFilterChanged)

        self.resetButton.clicked.connect(self.resetFilter)
        self.setButton.clicked.connect(self.applyFilter)

        self.retranslateUi()
        QtCore.QMetaObject.connectSlotsByName(self)

    def scrollTraceToBottom(self, parent, start, end):
        QtCore.QTimer.singleShot(0, self.TraceTable.scrollToBottom)

    def canIdFilterChanged(self, text):
        self.controller.can_id = text

    def canMaskFilterChanged(self, text):
        self.controller.can_mask = text

    def resetFilter(self):
        self.CanIDLineEdit.clear()
        self.maskLineEdit.clear()
        self.applyFilter()

    def applyFilter(self):
        # TODO
        return

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate
        self.groupBox.setTitle(_translate("TraceTab", "Filter Message"))
        self.CanIDLabel.setText(_translate("TraceTab", "CAN ID"))
        self.maskLabel.setText(_translate("TraceTab", "Mask"))
