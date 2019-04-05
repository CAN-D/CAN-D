from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QWidget, QFileDialog


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

        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
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
        icon.addPixmap(QtGui.QPixmap(":/icons/black/check_circle.svg"),
                       QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.setButton.setIcon(icon)
        self.setButton.setIconSize(QtCore.QSize(24, 24))
        self.setButton.setObjectName("setButton")
        self.horizontalLayout.addWidget(self.setButton, 0, QtCore.Qt.AlignTop)

        self.resetButton = QtWidgets.QPushButton(self.groupBox)
        self.resetButton.setMaximumSize(QtCore.QSize(48, 48))
        self.resetButton.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/icons/black/replay.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.resetButton.setIcon(icon1)
        self.resetButton.setIconSize(QtCore.QSize(24, 24))
        self.resetButton.setObjectName("resetButton")
        self.horizontalLayout.addWidget(self.resetButton)
        self.horizontalLayout_4.addWidget(
            self.groupBox, 0, QtCore.Qt.AlignLeft)

        self.groupBox_2 = QtWidgets.QGroupBox(self.TraceGroup)
        self.groupBox_2.setObjectName("groupBox_2")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.groupBox_2)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.pathEdit = QtWidgets.QLineEdit(self.groupBox_2)
        self.pathEdit.setMinimumSize(QtCore.QSize(500, 0))
        self.pathEdit.setMaximumSize(QtCore.QSize(1500, 16777215))
        self.pathEdit.setObjectName("pathEdit")
        self.horizontalLayout_3.addWidget(self.pathEdit)

        self.fileopenButton = QtWidgets.QPushButton(self.groupBox_2)
        self.fileopenButton.setMaximumSize(QtCore.QSize(40, 30))
        self.fileopenButton.setObjectName("fileopenButton")
        self.horizontalLayout_3.addWidget(
            self.fileopenButton, 0, QtCore.Qt.AlignLeft)

        self.setDbcButton = QtWidgets.QPushButton(self.groupBox_2)
        self.setDbcButton.setMaximumSize(QtCore.QSize(48, 48))
        self.setDbcButton.setText("")
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icons/black/check_circle.svg"),
                       QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.setDbcButton.setIcon(icon)
        self.setDbcButton.setIconSize(QtCore.QSize(24, 24))
        self.setDbcButton.setObjectName("setButton")
        self.horizontalLayout_3.addWidget(
            self.setDbcButton, 0, QtCore.Qt.AlignTop)

        self.horizontalLayout_4.addWidget(
            self.groupBox_2, 0, QtCore.Qt.AlignRight)
        self.verticalLayout_2.addLayout(self.horizontalLayout_4)

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
        self.pathEdit.textChanged.connect(self.pathEditChanged)

        self.resetButton.clicked.connect(self.resetFilter)
        self.setButton.clicked.connect(self.applyFilter)
        self.fileopenButton.clicked.connect(self.openFileDialog)

        self.retranslateUi()
        QtCore.QMetaObject.connectSlotsByName(self)

    def scrollTraceToBottom(self, parent, start, end):
        QtCore.QTimer.singleShot(0, self.TraceTable.scrollToBottom)

    def canIdFilterChanged(self, text):
        self.controller.can_id = text

    def canMaskFilterChanged(self, text):
        self.controller.can_mask = text

    def pathEditChanged(self, text):
        self.controller.dbcpath = text

    def resetFilter(self):
        self.CanIDLineEdit.clear()
        self.maskLineEdit.clear()
        self.applyFilter()

    def applyFilter(self):
        # TODO
        return

    def openFileDialog(self):
        self.pathEdit.setText(QFileDialog.getOpenFileName(self, 'Open File', './',
                                                          filter="All Files(*.*);;Text Files(*.txt)")[0])

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate
        self.groupBox.setTitle(_translate("TraceTab", "Filter Message"))
        self.CanIDLabel.setText(_translate("TraceTab", "CAN ID"))
        self.maskLabel.setText(_translate("TraceTab", "Mask"))
        self.groupBox_2.setTitle(_translate("TraceTab", "Import DBC File"))
        self.fileopenButton.setText(_translate("TraceTab", "..."))
