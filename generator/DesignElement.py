
""" base class for hierarchical design entities
"""
class DesignElement:
    # object initializer
    def __init__(self):
        self._childs = []
        self._name =""

    # sets the class name of the design element
    def setName(self, name):
        self._name = name

    # gets the class name of the design element
    def getName(self):
        return self._name

    # adds an child design element
    def addChild(self, el):
        self._childs.append(el)
