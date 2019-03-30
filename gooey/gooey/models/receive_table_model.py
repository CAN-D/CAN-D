from PyQt5.QtCore import (QModelIndex, QAbstractTableModel, Qt)
from models.receive_message import ReceiveMessage


class ReceiveTableModel(QAbstractTableModel):
    def __init__(self, parent=None, messages=None):
        super(ReceiveTableModel, self).__init__(parent)

        if messages is None:
            self.messages = []
        else:
            self.messages = messages

    """ Returns the number of rows this model holds. """

    def rowCount(self, index=QModelIndex()):
        return len(self.messages)

    """ Returns the number of columns this model holds. """

    def columnCount(self, index=QModelIndex()):
        # Documentation seem to always return a hard coded value. Probably in case self.messages is empty.
        return 6

    """ Depending on the index and role given, return data.
        If not returning data, return None
    """

    def data(self, index, role=Qt.DisplayRole):
        if not index.isValid():
            return None

        if not 0 <= index.row() < len(self.messages):
            return None

        if role == Qt.DisplayRole:
            can_id = self.messages[index.row()].can_id
            message = self.messages[index.row()].message
            dlc = self.messages[index.row()].dlc
            data = self.messages[index.row()].data
            cycle_time = self.messages[index.row()].cycle_time
            count = self.messages[index.row()].count

            if index.column() == 0:
                return can_id
            elif index.column() == 1:
                return message
            elif index.column() == 2:
                return dlc
            elif index.column() == 3:
                return cycle_time
            elif index.column() == 4:
                return count
            elif index.column() == 5:
                return data

        return None

    """ Set the headers to be displayed """

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

    """ Insert a row into the model. """

    def insertRow(self, newMessage, index=QModelIndex()):
        # Check if Table already has a message with the same name
        messageInTable = [
            m for m in self.messages if m.can_id == newMessage.can_id]

        if len(messageInTable) > 0:
            self.updateMessage(messageInTable[0], newMessage)
            self.dataChanged.emit(index, index)
        else:
            position = len(self.messages)
            self.beginInsertRows(QModelIndex(), position, position)
            self.messages.insert(position, newMessage)
            self.endInsertRows()

        return True

    def updateMessage(self, oldMessage, newMessage):
        oldMessage.can_id = newMessage.can_id
        oldMessage.message = newMessage.message
        oldMessage.dlc = newMessage.dlc
        oldMessage.data = newMessage.data
        oldMessage.cycle_time = float(newMessage.time) - float(oldMessage.time)
        oldMessage.count = oldMessage.count + 1

    """ Remove a row from the model. """

    def removeRow(self, position, rows=1, index=QModelIndex()):
        self.beginRemoveRows(QModelIndex(), position, position + rows - 1)
        del self.messages[position:position+rows]
        self.endRemoveRows()

        return True

    """ Adjust the data (set it to <value>) depending on the given index
        and role 
    """

    def setData(self, index, value, role=Qt.EditRole):
        if role != Qt.EditRole:
            return False

        if index.isValid() and 0 <= index.row() < len(self.messages):
            message = self.messages[index.row()]
            if index.column() == 0:
                message.can_id = value
            elif index.column() == 1:
                message.message = value
            elif index.column() == 2:
                message.dlc = value
            elif index.column() == 3:
                message.cycle_time = value
            elif index.column() == 4:
                message.count = value
            elif index.column() == 5:
                message.data = value
            else:
                False

            self.dataChanged.emit(index, index)
            return True

        return False

    """ Set the item flags at the given index. """

    def flags(self, index):

        if not index.isValid():
            return Qt.ItemIsEnabled

        return Qt.ItemFlags(QAbstractTableModel.flags(self, index) | Qt.ItemIsEditable)
