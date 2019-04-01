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

    def properties(self, column):
        self.itemModel.properties(column)

    def parent(self):
        return self.parentItem

    def row(self):
        if self.parentItem:
            return self.parentItem.childItems.index(self)

        return 0
