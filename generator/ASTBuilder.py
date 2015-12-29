import DesignElement
import Interface
import Controller


""" Extracts the design from XML description into an Abstract Syntax Tree
"""
class ASTBuilder:
    # object initializer
    def __init__(self, xmlroot):
        self._designroot = DesignElement
        self.visitNode( xmlroot )

    # handles given design element
    def checkElement(self, element):
        print(element.tag, element.attrib)

    # traverses XML tree pre-order
    def visitNode(self, element):
        self.checkElement(element)
        for child in element:
            self.visitNode(child)

    # gets the extracted AST
    def getAST(self):
        return self._designroot
