import ui.widgets.resources
import time
import cantools
import os.path
from PyQt5 import QtCore, QtGui, QtWidgets, Qt
from PyQt5.QtWidgets import QMainWindow, QLabel, QFileDialog
from candy_connector.parsers import parse_line
from can import Message
from ui.widgets.rxtx import RxTxTab
from ui.widgets.trace import TraceTab
from ui.widgets.connection import ConnectionsTab
from ui.widgets.transmit import TransmitWindow

from controllers.maincontroller import MainController, DataPollThread

from models.transmit_message import TransmitMessage
from models.receive_message import ReceiveMessage
from models.trace import Trace


class CAND_MainWindow(QMainWindow):
    sd_logging = "SD Card Logging " + u"\u2713"
    sd_not_logging = "SD Card Logging " + u"\u2718"
    connected = "   Connected to CAN-D USB!"
    disconnected = "   Disconnected"

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
        icon.addPixmap(QtGui.QPixmap(":/icons/open.png"),
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
        icon1.addPixmap(QtGui.QPixmap(":/icons/save.png"),
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
        icon2.addPixmap(QtGui.QPixmap(":/icons/connect1.png"),
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
        icon3.addPixmap(QtGui.QPixmap(":/icons/disconnect1.png"),
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
        icon4.addPixmap(QtGui.QPixmap(":/icons/sdstart.png"),
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
        icon5.addPixmap(QtGui.QPixmap(":/icons/sdstop.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.stopButton.setIcon(icon5)
        self.stopButton.setIconSize(QtCore.QSize(70, 70))
        self.stopButton.setObjectName("stopButton")
        self.sideBarLayout.addWidget(self.stopButton)

        # Play Button
        self.transmitButton = QtWidgets.QToolButton(self)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.transmitButton.sizePolicy().hasHeightForWidth())
        self.transmitButton.setSizePolicy(sizePolicy)
        icon6 = QtGui.QIcon()
        icon6.addPixmap(QtGui.QPixmap(":/icons/transmit.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.transmitButton.setIcon(icon6)
        self.transmitButton.setIconSize(QtCore.QSize(70, 70))
        self.transmitButton.setObjectName("transmitButton")
        self.sideBarLayout.addWidget(self.transmitButton)

        # Pause Button
        self.retransmitButton = QtWidgets.QToolButton(self)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.retransmitButton.sizePolicy().hasHeightForWidth())
        self.retransmitButton.setSizePolicy(sizePolicy)
        icon7 = QtGui.QIcon()
        icon7.addPixmap(QtGui.QPixmap(":/icons/retransmit.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.retransmitButton.setIcon(icon7)
        self.retransmitButton.setIconSize(QtCore.QSize(70, 70))
        self.retransmitButton.setObjectName("retransmitButton")
        self.sideBarLayout.addWidget(self.retransmitButton)

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

        self.openButton.clicked.connect(self.openFile)
        self.saveButton.clicked.connect(self.saveFile)
        self.connectButton.clicked.connect(self.connectUsb)
        self.disconnectButton.clicked.connect(self.disconnectUsb)
        self.recordButton.clicked.connect(self.startLoggingSD)
        self.stopButton.clicked.connect(self.stopLoggingSD)
        self.transmitButton.clicked.connect(self.transmitMessage)
        self.retransmitButton.clicked.connect(self.retransmitMessage)

        self.traceTab.setDbcButton.clicked.connect(self.setDbcCallback)

        self.connectedStatus = QLabel()
        self.connectedStatus.setText(CAND_MainWindow.disconnected)

        self.sdLoggingStatus = QLabel()
        self.sdLoggingStatus.setText(CAND_MainWindow.sd_not_logging)

        self.dbcStatus = QLabel()
        self.dbcStatus.setText("No DBC file selected")

        self.statusbar.addWidget(self.connectedStatus, 2)
        self.statusbar.addWidget(self.sdLoggingStatus, 3)
        self.statusbar.addPermanentWidget(self.dbcStatus)

        QtCore.QMetaObject.connectSlotsByName(self)

    def openFile(self):
        self.controller.open_file_path = QFileDialog.getOpenFileName(self, 'Open File', './',
                                                                     filter="CAN-D Trace Files(*.cand);;All Files(*.*);;Text Files(*.txt)")[0]
        if self.controller.open_file_path is not '':
            try:
                file = open(self.controller.open_file_path, "r")
                lines = file.readlines()
                for l in lines:
                    frame_id, payload = parse_line(l)
                    msg = Message()
                    msg.arbitration_id = frame_id
                    msg.dlc = len(payload)
                    msg.data = bytes(payload)
                    self.insertTrace(msg)
            except:
                popup = QtWidgets.QMessageBox.critical(
                    self, "Error", "Failed to open CAN-D trace file. \n\nFile must be of type .cand or .txt")
                return

    def saveFile(self):
        if self.controller.open_file_path is '':
            self.controller.open_file_path = QFileDialog.getSaveFileName(self, 'Save File', './',
                                                                         filter="CAN-D Trace Files (*.cand)")[0]

        try:
            file = open(self.controller.open_file_path, "w")
            for trace in self.controller.tracecontroller.tracetable.traces:
                arbitration_id = trace.can_id
                data = trace.data
                file.write(arbitration_id + " " + data + "\n")
        except:
            popup = QtWidgets.QMessageBox.critical(
                self, "Error", "Failed to save CAN-D trace file.")

    def connectUsb(self):
        if self.controller.connect():
            self.connectedStatus.setText(CAND_MainWindow.connected)
            self.connectButton.setEnabled(False)
            self.disconnectButton.setEnabled(True)
            self.startPoll()
        else:
            popup = QtWidgets.QMessageBox.critical(
                self, "Error", "CAN-D device not found. \n\nPlease make sure that the CAN-D is connected properly.")
            return

    def startPoll(self):
        self.poller = DataPollThread(self.controller.candbus)
        self.poller.start()
        self.poller.data_incoming.connect(self.insertTrace)

    def disconnectUsb(self):
        if not self.controller.disconnect():
            self.connectedStatus.setText(CAND_MainWindow.disconnected)
            self.connectButton.setEnabled(True)
            self.disconnectButton.setEnabled(False)
        else:
            popup = QtWidgets.QMessageBox.critical(
                self, "Error", "CAN-D device not found. \n\nPlease make sure that the CAN-D is connected properly.")
            return

    def startLoggingSD(self):
        if self.controller.startLog():
            self.sdLoggingStatus.setText(CAND_MainWindow.sd_logging)
            self.recordButton.setEnabled(False)
            self.stopButton.setEnabled(True)
        else:
            popup = QtWidgets.QMessageBox.critical(
                self, "Error", "CAN-D device is not connected. \n\nPlease connect to the CAN-D USB device.")
            return

    def stopLoggingSD(self):
        if not self.controller.stopLog():
            self.sdLoggingStatus.setText(CAND_MainWindow.sd_not_logging)
            self.recordButton.setEnabled(True)
            self.stopButton.setEnabled(False)
        else:
            popup = QtWidgets.QMessageBox.critical(
                self, "Error", "Stop logging SD card failed. \n\nPlease try again.")
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

        try:
            messagename = self.controller.dbc.get_message_by_frame_id(
                data.arbitration_id).name
        except:
            messagename = ""

        msg = ReceiveMessage(self.controller.rxtxcontroller.receivetable.rootItem,
                             self.formatId(hex(data.arbitration_id)),
                             messagename,
                             timestamp,
                             data.dlc,
                             self.formatHexData(data.data.hex()),
                             0,
                             1)

        self.controller.rxtxcontroller.appendReceiveTable(msg)
        self.controller.tracecontroller.appendTraceTable(msg)
        self.insertSignals(data, msg)

        return

    def insertSignals(self, data, msg):
        if self.controller.dbc is not None and msg.message is not "":
            decoded = self.controller.dbc.decode_message(
                data.arbitration_id, data.data)

            if len(decoded) > 0:
                for k, v in decoded.items():
                    signal = ReceiveMessage(parent=msg, message=k, data=v)
                    self.controller.rxtxcontroller.appendReceiveSignal(
                        msg, signal)

    def insertTransmit(self, data):
        msg = TransmitMessage()
        self.controller.rxtxcontroller.transmitMessage(msg)

    def setDbcCallback(self):
        if self.controller.tracecontroller.dbcpath is not None and os.path.exists(self.controller.tracecontroller.dbcpath):
            try:
                self.controller.dbc = cantools.database.load_file(
                    self.controller.tracecontroller.dbcpath)
                self.dbcStatus.setText(
                    "DBC file selected:  " + self.controller.tracecontroller.dbcpath)
            except ValueError as e:
                popup = QtWidgets.QMessageBox.critical(
                    self, "Error", "Failed to import DBC file. \n\n" + str(e))
                return
        else:
            self.controller.dbc = None

    def formatHexData(self, s):
        return (" ".join(s[i:i+2] for i in range(0, len(s), 2))).upper()

    def formatId(self, id):
        return id[0:2] + id[2:len(id)].upper()

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        self.setWindowTitle(_translate(
            "MainWindow", "CAN-D Data Logger"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(
            self.traceTab), _translate("MainWindow", "Trace"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(
            self.rxtxTab), _translate("MainWindow", "Receive/Transmit"))
        self.saveButton.setText(_translate("MainWindow", "..."))
        self.connectButton.setText(_translate("MainWindow", "..."))
        self.disconnectButton.setText(_translate("MainWindow", "..."))
        self.recordButton.setText(_translate("MainWindow", "..."))
        self.stopButton.setText(_translate("MainWindow", "..."))
        self.transmitButton.setText(_translate("MainWindow", "..."))
        self.retransmitButton.setText(_translate("MainWindow", "..."))
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
