import ui.widgets.resources
from PyQt5 import QtCore, QtGui, QtWidgets, QtSvg
from PyQt5.QtWidgets import QWidget
from models.clock_frequency import ClockFrequency
from models.bit_rate import BitRate
from models.connection import Connection


class ConnectionsTab(QWidget):
    def __init__(self):
        super().__init__()

        # TODO : set default value for connection
        self.model = Connection(
            clk_freq=ClockFrequency['ONE_MEGAHERTZ'],
            bitrate=BitRate['ONE_THOUSAND']
        )

        self.setObjectName("ConnectionsTab")
        self.verticalLayout = QtWidgets.QVBoxLayout(self)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")

        self.ConnectionsGroupBox = QtWidgets.QGroupBox(self)
        self.ConnectionsGroupBox.setTitle("")
        self.ConnectionsGroupBox.setObjectName("ConnectionsGroupBox")

        self.gridLayout = QtWidgets.QGridLayout(self.ConnectionsGroupBox)
        self.gridLayout.setObjectName("gridLayout")

        self.ConnectionsLabel = QtWidgets.QLabel(self)
        self.ConnectionsLabel.setMaximumSize(QtCore.QSize(200, 20))
        font = QtGui.QFont()
        font.setPointSize(18)
        self.ConnectionsLabel.setFont(font)
        self.ConnectionsLabel.setObjectName("ConnectionsLabel")

        self.horizontalLayoutLabel = QtWidgets.QHBoxLayout()
        self.horizontalLayoutLabel.setObjectName("horizontalLayoutLabel")
        self.connectionIcon = QtWidgets.QLabel()
        self.connectionIcon.setPixmap(QtGui.QPixmap(":/icons/power.svg"))

        # self.connectionIcon = QtSvg.QSvgWidget(':/icons/power.svg')
        # self.connectionIcon.setGeometry(0, 0, 24, 24)

        self.horizontalLayoutLabel.addWidget(self.connectionIcon)
        self.horizontalLayoutLabel.addWidget(self.ConnectionsLabel)

        self.gridLayout.addLayout(self.horizontalLayoutLabel, 0, 0, 1, 1)

        self.treeWidget = QtWidgets.QTreeWidget(self.ConnectionsGroupBox)
        self.treeWidget.setObjectName("treeWidget")
        item_0 = QtWidgets.QTreeWidgetItem(self.treeWidget)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_0 = QtWidgets.QTreeWidgetItem(self.treeWidget)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)
        item_1 = QtWidgets.QTreeWidgetItem(item_0)

        self.gridLayout.addWidget(self.treeWidget, 1, 0, 1, 1)

        self.horizontalLayout.addWidget(self.ConnectionsGroupBox, 1.5)

        self.ConnectionsLayout = QtWidgets.QVBoxLayout()
        self.ConnectionsLayout.setObjectName("ConnectionsLayout")
        self.groupBox = QtWidgets.QGroupBox(self)
        self.groupBox.setMinimumSize(QtCore.QSize(500, 0))
        self.groupBox.setMaximumSize(QtCore.QSize(16777215, 120))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.groupBox.setFont(font)
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.groupBox)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setSizeConstraint(
            QtWidgets.QLayout.SetMaximumSize)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout()
        self.verticalLayout_5.setContentsMargins(-1, -1, 40, -1)
        self.verticalLayout_5.setObjectName("verticalLayout_5")

        # Clock Frequency Combo Box
        self.clockFrequencyLabel = QtWidgets.QLabel(self.groupBox)
        self.clockFrequencyLabel.setMinimumSize(QtCore.QSize(0, 0))
        self.clockFrequencyLabel.setObjectName("clockFrequencyLabel")
        self.verticalLayout_5.addWidget(self.clockFrequencyLabel)
        self.clockFrequencyComboBox = QtWidgets.QComboBox(self.groupBox)
        self.clockFrequencyComboBox.setObjectName("clockFrequencyComboBox")
        self.verticalLayout_5.addWidget(self.clockFrequencyComboBox)
        self.setClockFrequencyOptions()
        self.clockFrequencyComboBox.currentIndexChanged.connect(
            self.clockFrequencyOptionsChanged)
        self.clockFrequencyComboBox.setCurrentIndex(
            self.getClockFrequencyIndex(self.model.clk_freq.value))

        self.horizontalLayout_2.addLayout(self.verticalLayout_5)
        self.verticalLayout_4 = QtWidgets.QVBoxLayout()
        self.verticalLayout_4.setContentsMargins(-1, -1, 40, -1)
        self.verticalLayout_4.setObjectName("verticalLayout_4")

        # Bit Rate Combo Box
        self.bitRateLabel = QtWidgets.QLabel(self.groupBox)
        self.bitRateLabel.setObjectName("bitRateLabel")
        self.verticalLayout_4.addWidget(self.bitRateLabel)
        self.bitRateComboBox = QtWidgets.QComboBox(self.groupBox)
        self.bitRateComboBox.setObjectName("bitRateComboBox")
        self.verticalLayout_4.addWidget(self.bitRateComboBox)
        self.setBitRateOptions()
        self.bitRateComboBox.currentIndexChanged.connect(
            self.bitRateOptionsChanged)
        self.bitRateComboBox.setCurrentIndex(
            self.getBitRateIndex(self.model.bitrate.value))

        # Set Settings button
        self.horizontalLayout_2.addLayout(self.verticalLayout_4)
        self.SetButton = QtWidgets.QPushButton(self.groupBox)
        self.SetButton.setMinimumSize(QtCore.QSize(36, 36))
        self.SetButton.setMaximumSize(QtCore.QSize(36, 36))
        self.SetButton.setAutoFillBackground(False)
        self.SetButton.setText("")
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icons/check_circle.svg"),
                       QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.SetButton.setIcon(icon)
        self.SetButton.setIconSize(QtCore.QSize(36, 36))
        self.SetButton.setObjectName("SetButton")
        self.horizontalLayout_2.addWidget(self.SetButton)

        # Reset Settings Button
        self.ResetDefaultButton = QtWidgets.QPushButton(self.groupBox)
        self.ResetDefaultButton.setEnabled(True)
        self.ResetDefaultButton.setMinimumSize(QtCore.QSize(36, 36))
        self.ResetDefaultButton.setMaximumSize(QtCore.QSize(36, 36))
        self.ResetDefaultButton.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/icons/replay.svg"),
                        QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ResetDefaultButton.setIcon(icon1)
        self.ResetDefaultButton.setIconSize(QtCore.QSize(36, 36))
        self.ResetDefaultButton.setObjectName("ResetDefaultButton")
        self.horizontalLayout_2.addWidget(self.ResetDefaultButton)

        self.verticalLayout_3.addLayout(self.horizontalLayout_2)
        self.ConnectionsLayout.addWidget(self.groupBox)
        spacerItem = QtWidgets.QSpacerItem(
            20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.ConnectionsLayout.addItem(spacerItem)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.connectButton = QtWidgets.QPushButton(self)
        self.connectButton.setObjectName("connectButton")
        self.horizontalLayout_3.addWidget(self.connectButton)
        self.disconnectButton = QtWidgets.QPushButton(self)
        self.disconnectButton.setObjectName("disconnectButton")
        self.horizontalLayout_3.addWidget(self.disconnectButton)
        self.ConnectionsLayout.addLayout(self.horizontalLayout_3)
        self.horizontalLayout.addLayout(self.ConnectionsLayout, 2)
        self.verticalLayout.addLayout(self.horizontalLayout)

        self.retranslateUi()
        QtCore.QMetaObject.connectSlotsByName(self)

    def retranslateUi(self):
        _translate = QtCore.QCoreApplication.translate
        self.setWindowTitle(_translate("ConnectionsTab", "Form"))
        self.ConnectionsLabel.setText(_translate(
            "ConnectionsTab", "Available Connections"))
        __sortingEnabled = self.treeWidget.isSortingEnabled()
        self.treeWidget.setSortingEnabled(False)
        self.treeWidget.topLevelItem(0).setText(
            0, _translate("ConnectionsTab", "CAN-D USB"))
        self.treeWidget.topLevelItem(0).child(0).setText(
            0, _translate("ConnectionsTab", "USB01 (500kbit/s)"))
        self.treeWidget.topLevelItem(0).child(1).setText(
            0, _translate("ConnectionsTab", "USB02 (500kbit/s)"))
        self.treeWidget.topLevelItem(1).setText(
            0, _translate("ConnectionsTab", "CAN-D Wireless"))
        self.treeWidget.topLevelItem(1).child(0).setText(
            0, _translate("ConnectionsTab", "BT01"))
        self.treeWidget.topLevelItem(1).child(1).setText(
            0, _translate("ConnectionsTab", "BT02"))
        self.treeWidget.setSortingEnabled(__sortingEnabled)
        self.groupBox.setTitle(_translate(
            "ConnectionsTab", "Connection Settings"))
        self.clockFrequencyLabel.setText(
            _translate("ConnectionsTab", "Clock Frequency"))
        self.bitRateLabel.setText(_translate("ConnectionsTab", "Bit Rate"))
        self.connectButton.setText(_translate("ConnectionsTab", "Connect"))
        self.disconnectButton.setText(
            _translate("ConnectionsTab", "Disconnect"))

    def setClockFrequencyOptions(self):
        self.clockFrequencyItems = [e.value for e in ClockFrequency]
        self.clockFrequencyComboBox.addItems(self.clockFrequencyItems)

    def getClockFrequencyIndex(self, selectedItem):
        return self.clockFrequencyItems.index(selectedItem)

    def setBitRateOptions(self):
        self.bitRateItems = [e.value for e in BitRate]
        self.bitRateComboBox.addItems(self.bitRateItems)

    def getBitRateIndex(self, selectedItem):
        return self.bitRateItems.index(selectedItem)

    def clockFrequencyOptionsChanged(self, i):
        print("Clock changed to index: ", i, " which is: ",
              self.clockFrequencyComboBox.currentText())

        self.model.setClockFrequency(self.clockFrequencyComboBox.currentText())

    def bitRateOptionsChanged(self, i):
        print("Clock changed to index: ", i,
              " which is: ", self.bitRateComboBox.currentText())

        self.model.setBitRate(self.bitRateComboBox.currentText())


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    ui = ConnectionsTab()
    ui.show()
    sys.exit(app.exec_())
