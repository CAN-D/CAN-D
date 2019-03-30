import ui.widgets.resources
import time
from PyQt5 import QtCore, QtGui, QtWidgets, Qt
from PyQt5.QtWidgets import QMainWindow
from ui.widgets.rxtx import RxTxTab
from ui.widgets.trace import TraceTab
from ui.widgets.connection import ConnectionsTab
from ui.widgets.transmit import TransmitWindow

from controllers.maincontroller import MainController, DataPollThread

from models.transmit_message import TransmitMessage
from models.receive_message import ReceiveMessage
from models.trace import Trace


class CAND_MainWindow(QMainWindow):
    def __init__(self, isdemo=False, trace_location=None):
        super().__init__()

        self.controller = MainController(isdemo, trace_location)
        self.title = 'CAN-D Automotive Datalogger'

        self.setObjectName("MainWindow")
        self.resize(1280, 778)
        self.setAutoFillBackground(False)
        self.centralwidget = QtWidgets.QWidget(self)
        self.centralwidget.setObjectName("centralwidget")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setGeometry(QtCore.QRect(90, 10, 1181, 741))
        self.tabWidget.setTabPosition(QtWidgets.QTabWidget.North)
        self.tabWidget.setMovable(True)
        self.tabWidget.setObjectName("tabWidget")

        # Trace Tab
        self.traceTab = TraceTab(self.controller.tracecontroller)
        self.tabWidget.addTab(self.traceTab, "")

        # Receive/Transmit Tab
        self.rxtxTab = RxTxTab(self.controller.rxtxcontroller)
        self.tabWidget.addTab(self.rxtxTab, "")

        # Connections Tab
        self.connectionTab = ConnectionsTab()
        self.tabWidget.addTab(self.connectionTab, "")

        # GPS Tab
        self.gpsTab = QtWidgets.QWidget()
        self.tabWidget.addTab(self.gpsTab, "")

        self.layoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget.setGeometry(QtCore.QRect(0, 20, 82, 731))
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.layoutWidget.sizePolicy().hasHeightForWidth())
        self.layoutWidget.setSizePolicy(sizePolicy)
        self.layoutWidget.setObjectName("layoutWidget")

        self.sideBarLayout = QtWidgets.QVBoxLayout(self.layoutWidget)
        self.sideBarLayout.setSizeConstraint(QtWidgets.QLayout.SetMaximumSize)
        self.sideBarLayout.setContentsMargins(0, 0, 0, 0)
        self.sideBarLayout.setObjectName("sideBarLayout")

        # Open Button
        self.openButton = QtWidgets.QToolButton(self)

        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.openButton.sizePolicy().hasHeightForWidth())
        self.openButton.setSizePolicy(sizePolicy)

        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icons/open.svg"),
                       QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.openButton.setIcon(icon)
        self.openButton.setIconSize(QtCore.QSize(70, 70))
        self.openButton.setObjectName("openButton")

        self.sideBarLayout.addWidget(self.openButton)

        # Save Button
        self.saveButton = QtWidgets.QToolButton(self)

        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.saveButton.sizePolicy().hasHeightForWidth())
        self.saveButton.setSizePolicy(sizePolicy)

        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/icons/save.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.saveButton.setIcon(icon1)
        self.saveButton.setIconSize(QtCore.QSize(70, 70))
        self.saveButton.setObjectName("saveButton")

        self.sideBarLayout.addWidget(self.saveButton)

        # Connect Button
        self.connectButton = QtWidgets.QToolButton(self)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.connectButton.sizePolicy().hasHeightForWidth())
        self.connectButton.setSizePolicy(sizePolicy)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/icons/connect.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.connectButton.setIcon(icon2)
        self.connectButton.setIconSize(QtCore.QSize(70, 70))
        self.connectButton.setObjectName("connectButton")
        self.sideBarLayout.addWidget(self.connectButton)

        # Disconnect Button
        self.disconnectButton = QtWidgets.QToolButton(self)
        self.disconnectButton.setEnabled(False)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.disconnectButton.sizePolicy().hasHeightForWidth())
        self.disconnectButton.setSizePolicy(sizePolicy)
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/icons/disconnect.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.disconnectButton.setIcon(icon3)
        self.disconnectButton.setIconSize(QtCore.QSize(70, 70))
        self.disconnectButton.setObjectName("disconnectButton")
        self.sideBarLayout.addWidget(self.disconnectButton)

        # Record Button
        self.recordButton = QtWidgets.QToolButton(self)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.recordButton.sizePolicy().hasHeightForWidth())
        self.recordButton.setSizePolicy(sizePolicy)
        icon4 = QtGui.QIcon()
        icon4.addPixmap(QtGui.QPixmap(":/icons/record.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.recordButton.setIcon(icon4)
        self.recordButton.setIconSize(QtCore.QSize(70, 70))
        self.recordButton.setObjectName("recordButton")
        self.sideBarLayout.addWidget(self.recordButton)

        # Stop Button
        self.stopButton = QtWidgets.QToolButton(self)
        self.stopButton.setEnabled(False)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.stopButton.sizePolicy().hasHeightForWidth())
        self.stopButton.setSizePolicy(sizePolicy)
        icon5 = QtGui.QIcon()
        icon5.addPixmap(QtGui.QPixmap(":/icons/stop.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.stopButton.setIcon(icon5)
        self.stopButton.setIconSize(QtCore.QSize(70, 70))
        self.stopButton.setObjectName("stopButton")
        self.sideBarLayout.addWidget(self.stopButton)

        # Play Button
        self.playButton = QtWidgets.QToolButton(self)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.playButton.sizePolicy().hasHeightForWidth())
        self.playButton.setSizePolicy(sizePolicy)
        icon6 = QtGui.QIcon()
        icon6.addPixmap(QtGui.QPixmap(":/icons/play.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.playButton.setIcon(icon6)
        self.playButton.setIconSize(QtCore.QSize(70, 70))
        self.playButton.setObjectName("playButton")
        self.sideBarLayout.addWidget(self.playButton)

        # Pause Button
        self.pauseButton = QtWidgets.QToolButton(self)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.pauseButton.sizePolicy().hasHeightForWidth())
        self.pauseButton.setSizePolicy(sizePolicy)
        icon7 = QtGui.QIcon()
        icon7.addPixmap(QtGui.QPixmap(":/icons/pause.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pauseButton.setIcon(icon7)
        self.pauseButton.setIconSize(QtCore.QSize(70, 70))
        self.pauseButton.setObjectName("pauseButton")
        self.sideBarLayout.addWidget(self.pauseButton)

        self.setCentralWidget(self.centralwidget)

        # Set MenuBar Widget
        self.menubar = QtWidgets.QMenuBar(self)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1280, 22))
        self.menubar.setObjectName("menubar")
        self.menuCAN_D = QtWidgets.QMenu(self.menubar)
        self.menuCAN_D.setObjectName("menuCAN_D")
        self.menuFile = QtWidgets.QMenu(self.menuCAN_D)
        self.menuFile.setObjectName("menuFile")
        self.setMenuBar(self.menubar)

        # Status Bar
        self.statusbar = QtWidgets.QStatusBar(self)
        self.statusbar.setObjectName("statusbar")
        self.setStatusBar(self.statusbar)
        self.statusbar.showMessage(
            "Disconnected | SD Card Logging " + u"\u2718")

        # Actions
        self.actionFile_2 = QtWidgets.QAction(self)
        self.actionFile_2.setObjectName("actionFile_2")
        self.actionSave = QtWidgets.QAction(self)
        self.actionSave.setObjectName("actionSave")
        self.actionSave_As = QtWidgets.QAction(self)
        self.actionSave_As.setObjectName("actionSave_As")
        self.menuFile.addAction(self.actionFile_2)
        self.menuFile.addAction(self.actionSave)
        self.menuFile.addAction(self.actionSave_As)
        self.menuCAN_D.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuCAN_D.menuAction())

        self.retranslateUi(self)
        self.tabWidget.setCurrentIndex(0)

        self.connectButton.clicked.connect(self.connectUsb)
        self.disconnectButton.clicked.connect(self.disconnectUsb)

        # TODO REMOVE THESE, ONLY FOR TEST
        self.saveButton.clicked.connect(self.insertTransmit)

        self.playButton.clicked.connect(self.transmitMessage)
        self.pauseButton.clicked.connect(self.retransmitMessage)

        QtCore.QMetaObject.connectSlotsByName(self)

    def connectUsb(self):
        if self.controller.connect():
            self.statusbar.showMessage(
                "Connected | SD Card Logging " + u"\u2718")
            self.connectButton.setEnabled(False)
            self.disconnectButton.setEnabled(True)
            self.startPoll()
        else:
            # TODO show pop-up for cant connect
            return

    def startPoll(self):
        self.poller = DataPollThread(self.controller.candbus)
        self.poller.start()
        self.poller.data_incoming.connect(self.insertTrace)

    def disconnectUsb(self):
        if not self.controller.disconnect():
            self.statusbar.showMessage(
                "Disconnected | SD Card Logging " + u"\u2718")
            self.connectButton.setEnabled(True)
            self.disconnectButton.setEnabled(False)
        else:
            # TODO show pop-up for cant disconnect
            return

    def startLoggingSD(self):
        if self.controller.startLog():
            self.statusbar.showMessage(
                "Connected | SD Card Logging " + u"\u2713")
            self.recordButton.setEnabled(False)
            self.stopButton.setEnabled(True)
        else:
            # TODO show pop-up for cant log SD
            return

    def stopLoggingSD(self):
        if not self.controller.stopLog():
            self.statusbar.showMessage(
                "Connected | SD Card Logging " + u"\u2718")
            self.recordButton.setEnabled(False)
            self.stopButton.setEnabled(True)
        else:
            # TODO show pop-up for cant log SD
            return

    def transmitMessage(self):
        transmitWindow = TransmitWindow(self)
        transmitWindow.show()

        if transmitWindow.exec_():
            self.controller.rxtxcontroller.transmitMessage(
                transmitWindow.message)

    def retransmitMessage(self):
        selected = self.rxtxTab.transmitTable.selectionModel()
        if selected.hasSelection():
            for row in selected.selectedRows():
                message = self.rxtxTab.controller.transmittable.messages[row.row(
                )]
                self.controller.rxtxcontroller.transmitMessage(message)

    def insertTrace(self, data):
        if data.timestamp is None:
            timestamp = int(round(time.time() * 1000))
        else:
            timestamp = data.timestamp

        # TODO, get message by using DBC
        messagename = ""

        msg = ReceiveMessage(hex(data.arbitration_id), messagename,
                             timestamp, data.dlc, data.data.hex(), 0, 1)

        self.controller.rxtxcontroller.appendReceiveTable(msg)
        self.controller.tracecontroller.appendTraceTable(msg)

    def insertTransmit(self, data):
        msg = TransmitMessage()
        self.controller.rxtxcontroller.transmitMessage(msg)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        self.setWindowTitle(_translate(
            "MainWindow", "CAN-D Data Logger"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(
            self.traceTab), _translate("MainWindow", "Trace"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(
            self.rxtxTab), _translate("MainWindow", "Receive/Transmit"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(
            self.connectionTab), _translate("MainWindow", "Connections"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(
            self.gpsTab), _translate("MainWindow", "GPS"))
        self.saveButton.setText(_translate("MainWindow", "..."))
        self.connectButton.setText(_translate("MainWindow", "..."))
        self.disconnectButton.setText(_translate("MainWindow", "..."))
        self.recordButton.setText(_translate("MainWindow", "..."))
        self.stopButton.setText(_translate("MainWindow", "..."))
        self.playButton.setText(_translate("MainWindow", "..."))
        self.pauseButton.setText(_translate("MainWindow", "..."))
        self.menuCAN_D.setTitle(_translate("MainWindow", "CAN-D"))
        self.menuFile.setTitle(_translate("MainWindow", "File"))
        self.actionFile_2.setText(_translate("MainWindow", "Open..."))
        self.actionSave.setText(_translate("MainWindow", "Save"))
        self.actionSave_As.setText(_translate("MainWindow", "Save As ..."))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    ui = CAND_MainWindow()
    ui.show()
    sys.exit(app.exec_())
