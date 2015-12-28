
""" the hierarchical design
"""
class DesignElement:
    def __init__(self):
        self._childs = []

    def addChild(self, el):
        self._childs.append(el)
