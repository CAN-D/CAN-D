from PyQt5 import QtCore


class Messages(QtCore.QAbstractTableModel):
    def __init__(self, parent=None, *args):
        super(Messages, self).__init__()
        self.datatable = None

    def update(self, dataIn):
        print('Updating model')
        self.datatable = dataIn
        print('Datatable : {0}').format(self.datatable)

    def rowCount(self, parent=QtCore.QModelIndex()):
        return len(self.datatable.index)

    def columnCount(self, parent=QtCore.QModelIndex()):
        return len(self.datatable.columns.values)

    def data(self, index, role=QtCore.Qt.DisplayRole):
        if role == QtCore.Qt.DisplayRole:
            i = index.row()
            j = index.column()
            return '{0}'.format(self.datatable.iget_value(i, j))
        else:
            return QtCore.QVariant()

    def flags(self, index):
        return QtCore.Qt.ItemIsEnabled
