

from DesignElement import *

""" Represents an abstract interface to create polymorphy in the design
"""

class Interface(DesignElement):
    def __init__(self):
        super(Interface,self).__init__()
        self._functions = []
