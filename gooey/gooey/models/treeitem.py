class TreeItem(object):
    """ A base class for models that is to be represented as a tree.

        :param `parentItem`: The parent of the TreeItem.
        :param `itemModel`: The model which holds the data for the TreeItem.
        :param `childItems`: The children of the TreeItem.
    """
    def __init__(self, model, parent=None):
        self.parentItem = parent
        self.itemModel = model
        self.childItems = []

    def appendChild(self, item):
        """ Append a child to the TreeItem
        
            Arguments:
                item {Object} - the child to be appended.
        """
        self.childItems.append(item)

    def child(self, row):
        """ Return the child at the given row index.
            
            Arguments:
                row {integer} - The index of the child.
            
            Returns:
                Object - The child at index `row`.
        """
        return self.childItems[row]

    def childCount(self):
        """ Returns the number of children.
        """
        return len(self.childItems)

    def columnCount(self):
        """ Returns the number of columns.
        """
        return 6

    def properties(self, column):
        """ Returns the property value at the given column index.
        
        Arguments:
            column {integer} - the column index where the data is to be displayed
        """
        
        self.itemModel.properties(column)

    def parent(self):
        """ Returns the parent of the TreeItem.
        """
        return self.parentItem

    def row(self):
        """ Returns the QModelIndex of the TreeItem
        """
        if self.parentItem:
            return self.parentItem.childItems.index(self)

        return 0
