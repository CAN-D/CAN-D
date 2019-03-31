from PyQt5 import QtCore, Qt
from PyQt5.QtCore import QAbstractItemModel, QModelIndex
from models.receive_message import ReceiveMessage


class TreeItem(object):
    def __init__(self, model, parent=None):
        self.parentItem = parent
        self.itemModel = model
        self.childItems = []

    def appendChild(self, item):
        self.childItems.append(item)

    def child(self, row):
        return self.childItems[row]

    def childCount(self):
        return len(self.childItems)

    def columnCount(self):
        return 6

    def data(self, column):
        if column == 0:
            return self.itemModel.can_id
        elif column == 1:
            return self.itemModel.message
        elif column == 2:
            return self.itemModel.dlc
        elif column == 3:
            return self.itemModel.cycle_time
        elif column == 4:
            return self.itemModel.count
        elif column == 5:
            return self.itemModel.data

    def parent(self):
        return self.parentItem

    def row(self):
        if self.parentItem:
            return self.parentItem.childItems.index(self)

        return 0


class TreeModel(QAbstractItemModel):
    def __init__(self, data, parent=None):
        super(TreeModel, self).__init__(parent)
        self.rootItem = ReceiveMessage()

    def columnCount(self, parent):
        if parent.isValid():
            return parent.internalPointer().columnCount()
        else:
            return self.rootItem.columnCount()

    def data(self, index, role):
        if not index.isValid():
            return None

        if role != QtCore.Qt.DisplayRole:
            return None

        item = index.internalPointer()

        return item.data(index.column())

    def flags(self, index):
        if not index.isValid():
            return QtCore.Qt.NoItemFlags

        return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable

    def headerData(self, section, orientation, role=Qt.DisplayRole):
        if role != Qt.DisplayRole:
            return None

        if orientation == Qt.Horizontal:
            if section == 0:
                return "CAN ID"
            elif section == 1:
                return "Message"
            elif section == 2:
                return "DLC"
            elif section == 3:
                return "Cycle Time"
            elif section == 4:
                return "Count"
            elif section == 5:
                return "Data"

        return None

    def index(self, row, column, parent):
        if not self.hasIndex(row, column, parent):
            return QtCore.QModelIndex()

        if not parent.isValid():
            parentItem = self.rootItem
        else:
            parentItem = parent.internalPointer()

        childItem = parentItem.child(row)
        if childItem:
            return self.createIndex(row, column, childItem)
        else:
            return QtCore.QModelIndex()

    def parent(self, index):
        if not index.isValid():
            return QtCore.QModelIndex()

        childItem = index.internalPointer()
        parentItem = childItem.parent()

        if parentItem == self.rootItem:
            return QtCore.QModelIndex()

        return self.createIndex(parentItem.row(), 0, parentItem)

    def rowCount(self, parent):
        if parent.column() > 0:
            return 0

        if not parent.isValid():
            parentItem = self.rootItem
        else:
            parentItem = parent.internalPointer()

        return parentItem.childCount()

    def insertRow(self, newMessage, index=QModelIndex()):
        # Check if Table already has a message with the same name
        messageInTable = [
            m for m in self.rootItem.childItems if m.can_id == newMessage.can_id]

        if len(messageInTable) > 0:
            self.updateMessage(messageInTable[0], newMessage)
            self.dataChanged.emit(index, index)
        else:
            position = len(self.messages)
            self.beginInsertRows(QModelIndex(), position, position)
            self.rootItem.childItems.insert(position, newMessage)
            self.endInsertRows()

        return True

    def updateMessage(self, oldMessage, newMessage):
        oldMessage.can_id = newMessage.can_id
        oldMessage.message = newMessage.message
        oldMessage.dlc = newMessage.dlc
        oldMessage.data = newMessage.data
        oldMessage.cycle_time = float(newMessage.time) - float(oldMessage.time)
        oldMessage.count = oldMessage.count + 1
