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

        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.sideBarLayout = QtWidgets.QVBoxLayout()
        self.sideBarLayout.setSizeConstraint(QtWidgets.QLayout.SetMaximumSize)
        self.sideBarLayout.setObjectName("sideBarLayout")

        ###  Buttons  ###

        # Open Button
        self.openButton = QtWidgets.QToolButton(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.openButton.sizePolicy().hasHeightForWidth())
        self.openButton.setSizePolicy(sizePolicy)
        self.openButton.setMinimumSize(QtCore.QSize(60, 60))
        self.openButton.setMaximumSize(QtCore.QSize(60, 60))
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icons/white/open.png"),
                       QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon.addPixmap(QtGui.QPixmap(":/icons/white/open.png"),
                       QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon.addPixmap(QtGui.QPixmap(":/icons/white/open.png"),
                       QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.openButton.setIcon(icon)
        self.openButton.setIconSize(QtCore.QSize(30, 30))
        self.openButton.setObjectName("openButton")
        self.sideBarLayout.addWidget(self.openButton, 0, QtCore.Qt.AlignLeft)

        # Save Button
        self.saveButton = QtWidgets.QToolButton(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.saveButton.sizePolicy().hasHeightForWidth())
        self.saveButton.setSizePolicy(sizePolicy)
        self.saveButton.setMinimumSize(QtCore.QSize(60, 60))
        self.saveButton.setMaximumSize(QtCore.QSize(60, 60))
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/icons/white/save.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon1.addPixmap(QtGui.QPixmap(":/icons/white/save.png"),
                        QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon1.addPixmap(QtGui.QPixmap(":/icons/white/save.png"),
                        QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.saveButton.setIcon(icon1)
        self.saveButton.setIconSize(QtCore.QSize(30, 30))
        self.saveButton.setObjectName("saveButton")
        self.sideBarLayout.addWidget(self.saveButton, 0, QtCore.Qt.AlignLeft)

        # Connect Button
        self.connectButton = QtWidgets.QToolButton(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.connectButton.sizePolicy().hasHeightForWidth())
        self.connectButton.setSizePolicy(sizePolicy)
        self.connectButton.setMinimumSize(QtCore.QSize(60, 60))
        self.connectButton.setMaximumSize(QtCore.QSize(60, 60))
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/icons/white/connect1.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon2.addPixmap(QtGui.QPixmap(":/icons/white/connect1.png"),
                        QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon2.addPixmap(QtGui.QPixmap(":/icons/white/connect1.png"),
                        QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.connectButton.setIcon(icon2)
        self.connectButton.setIconSize(QtCore.QSize(30, 30))
        self.connectButton.setObjectName("connectButton")
        self.sideBarLayout.addWidget(
            self.connectButton, 0, QtCore.Qt.AlignLeft)

        # Disconnect Button
        self.disconnectButton = QtWidgets.QToolButton(self.centralwidget)
        self.disconnectButton.setEnabled(False)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.disconnectButton.sizePolicy().hasHeightForWidth())
        self.disconnectButton.setSizePolicy(sizePolicy)
        self.disconnectButton.setMinimumSize(QtCore.QSize(60, 60))
        self.disconnectButton.setMaximumSize(QtCore.QSize(60, 60))
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/icons/white/disconnect1.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon3.addPixmap(QtGui.QPixmap(":/icons/white/disconnect1.png"),
                        QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon3.addPixmap(QtGui.QPixmap(":/icons/white/disconnect1.png"),
                        QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.disconnectButton.setIcon(icon3)
        self.disconnectButton.setIconSize(QtCore.QSize(30, 30))
        self.disconnectButton.setObjectName("disconnectButton")
        self.sideBarLayout.addWidget(
            self.disconnectButton, 0, QtCore.Qt.AlignLeft)

        # Start SD Button
        self.startSdButton = QtWidgets.QToolButton(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.startSdButton.sizePolicy().hasHeightForWidth())
        self.startSdButton.setSizePolicy(sizePolicy)
        self.startSdButton.setMinimumSize(QtCore.QSize(60, 60))
        self.startSdButton.setMaximumSize(QtCore.QSize(60, 60))
        icon4 = QtGui.QIcon()
        icon4.addPixmap(QtGui.QPixmap(":/icons/white/sdstart.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon4.addPixmap(QtGui.QPixmap(":/icons/white/sdstart.png"),
                        QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon4.addPixmap(QtGui.QPixmap(":/icons/white/sdstop.png"),
                        QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.startSdButton.setIcon(icon4)
        self.startSdButton.setIconSize(QtCore.QSize(30, 30))
        self.startSdButton.setObjectName("startSdButton")
        self.sideBarLayout.addWidget(
            self.startSdButton, 0, QtCore.Qt.AlignLeft)

        # Stop SD Button
        self.stopSdButton = QtWidgets.QToolButton(self.centralwidget)
        self.stopSdButton.setEnabled(False)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.stopSdButton.sizePolicy().hasHeightForWidth())
        self.stopSdButton.setSizePolicy(sizePolicy)
        self.stopSdButton.setMinimumSize(QtCore.QSize(60, 60))
        self.stopSdButton.setMaximumSize(QtCore.QSize(60, 60))
        icon5 = QtGui.QIcon()
        icon5.addPixmap(QtGui.QPixmap(":/icons/white/sdstop.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon5.addPixmap(QtGui.QPixmap(":/icons/white/sdstop.png"),
                        QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon5.addPixmap(QtGui.QPixmap(":/icons/white/sdstop.png"),
                        QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.stopSdButton.setIcon(icon5)
        self.stopSdButton.setIconSize(QtCore.QSize(30, 30))
        self.stopSdButton.setObjectName("stopSdButton")
        self.sideBarLayout.addWidget(self.stopSdButton, 0, QtCore.Qt.AlignLeft)

        # Transmit Button
        self.transmitButton = QtWidgets.QToolButton(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.transmitButton.sizePolicy().hasHeightForWidth())
        self.transmitButton.setSizePolicy(sizePolicy)
        self.transmitButton.setMinimumSize(QtCore.QSize(60, 60))
        self.transmitButton.setMaximumSize(QtCore.QSize(60, 60))
        icon6 = QtGui.QIcon()
        icon6.addPixmap(QtGui.QPixmap(":/icons/white/transmit.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon6.addPixmap(QtGui.QPixmap(":/icons/white/transmit.png"),
                        QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon6.addPixmap(QtGui.QPixmap(":/icons/white/transmit.png"),
                        QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.transmitButton.setIcon(icon6)
        self.transmitButton.setIconSize(QtCore.QSize(30, 30))
        self.transmitButton.setObjectName("transmitButton")
        self.sideBarLayout.addWidget(
            self.transmitButton, 0, QtCore.Qt.AlignLeft)

        # Retransmit Button
        self.retransmitButton = QtWidgets.QToolButton(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.retransmitButton.sizePolicy().hasHeightForWidth())
        self.retransmitButton.setSizePolicy(sizePolicy)
        self.retransmitButton.setMinimumSize(QtCore.QSize(60, 60))
        self.retransmitButton.setMaximumSize(QtCore.QSize(60, 60))
        icon7 = QtGui.QIcon()
        icon7.addPixmap(QtGui.QPixmap(":/icons/white/retransmit.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon7.addPixmap(QtGui.QPixmap(":/icons/white/retransmit.png"),
                        QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon7.addPixmap(QtGui.QPixmap(":/icons/white/retransmit.png"),
                        QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.retransmitButton.setIcon(icon7)
        self.retransmitButton.setIconSize(QtCore.QSize(30, 30))
        self.retransmitButton.setObjectName("retransmitButton")
        self.sideBarLayout.addWidget(
            self.retransmitButton, 0, QtCore.Qt.AlignLeft)

        # Mark Button
        self.markButton = QtWidgets.QToolButton(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(
            QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.markButton.sizePolicy().hasHeightForWidth())
        self.markButton.setSizePolicy(sizePolicy)
        self.markButton.setMaximumSize(QtCore.QSize(60, 60))
        icon8 = QtGui.QIcon()
        icon8.addPixmap(QtGui.QPixmap(":/icons/white/mark.png"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon8.addPixmap(QtGui.QPixmap(":/icons/white/mark.png"),
                        QtGui.QIcon.Active, QtGui.QIcon.Off)
        icon8.addPixmap(QtGui.QPixmap(":/icons/white/mark.png"),
                        QtGui.QIcon.Selected, QtGui.QIcon.Off)
        self.markButton.setIcon(icon8)
        self.markButton.setIconSize(QtCore.QSize(30, 30))
        self.markButton.setObjectName("markButton")
        self.sideBarLayout.addWidget(self.markButton)
        self.horizontalLayout_2.addLayout(self.sideBarLayout)

        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setTabPosition(QtWidgets.QTabWidget.North)
        self.tabWidget.setMovable(True)
        self.tabWidget.setObjectName("tabWidget")

        # Trace Tab
        self.traceTab = TraceTab(self.controller.tracecontroller)
        self.tabWidget.addTab(self.traceTab, "")

        # Receive/Transmit Tab
        self.rxtxTab = RxTxTab(self.controller.rxtxcontroller)
        self.tabWidget.addTab(self.rxtxTab, "")

        self.horizontalLayout_2.addWidget(self.tabWidget)
        self.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(self)
        self.statusbar.setObjectName("statusbar")
        self.statusbar.setStyleSheet("font: 13pt\".Avenir Next LT Pro\";")
        self.setStatusBar(self.statusbar)

        self.retranslateUi(self)
        self.tabWidget.setCurrentIndex(0)

        self.openButton.clicked.connect(self.openFile)
        self.saveButton.clicked.connect(self.saveFile)
        self.connectButton.clicked.connect(self.connectUsb)
        self.disconnectButton.clicked.connect(self.disconnectUsb)
        self.startSdButton.clicked.connect(self.startLoggingSD)
        self.stopSdButton.clicked.connect(self.stopLoggingSD)
        self.transmitButton.clicked.connect(self.transmitMessage)
        self.retransmitButton.clicked.connect(self.retransmitMessage)
        self.markButton.clicked.connect(self.markLog)

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
            self.startSdButton.setEnabled(False)
            self.stopSdButton.setEnabled(True)
            self.markButton.setEnabled(True)
        else:
            popup = QtWidgets.QMessageBox.critical(
                self, "Error", "CAN-D device is not connected. \n\nPlease connect to the CAN-D USB device.")
            return

    def stopLoggingSD(self):
        if not self.controller.stopLog():
            self.sdLoggingStatus.setText(CAND_MainWindow.sd_not_logging)
            self.startSdButton.setEnabled(True)
            self.stopSdButton.setEnabled(False)
            self.markButton.setEnabled(False)
        else:
            popup = QtWidgets.QMessageBox.critical(
                self, "Error", "Stop logging SD card failed. \n\nPlease try again.")
            return

    def transmitMessage(self):
        transmitWindow = TransmitWindow(self, self.controller.rxtxcontroller)
        transmitWindow.show()

        if transmitWindow.exec_():
            self.controller.rxtxcontroller.transmitMessage(
                transmitWindow.message)

    def retransmitMessage(self):
        selected = self.rxtxTab.transmitTable.selectionModel()
        if selected.hasSelection():
            for row in selected.selectedRows():
                message = self.rxtxTab.controller.transmittable.rootItem.childItems[row.row(
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

    def markLog(self):
        if not self.controller.markLog():
            popup = QtWidgets.QMessageBox.critical(
                self, "Error", "Mark data log failed. \n\nPlease try again.")
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
        MainWindow.setWindowTitle(_translate(
            "MainWindow", "CAN-D Data Logger"))
        self.saveButton.setText(_translate("MainWindow", "..."))
        self.connectButton.setText(_translate("MainWindow", "..."))
        self.disconnectButton.setText(_translate("MainWindow", "..."))
        self.startSdButton.setText(_translate("MainWindow", "..."))
        self.stopSdButton.setText(_translate("MainWindow", "..."))
        self.transmitButton.setText(_translate("MainWindow", "..."))
        self.retransmitButton.setText(_translate("MainWindow", "..."))
        self.markButton.setText(_translate("MainWindow", "..."))
        self.tabWidget.setTabText(self.tabWidget.indexOf(
            self.traceTab), _translate("MainWindow", "Trace"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(
            self.rxtxTab), _translate("MainWindow", "Receive/Transmit"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    ui = CAND_MainWindow()
    ui.show()
    sys.exit(app.exec_())
