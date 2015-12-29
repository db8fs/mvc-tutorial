
import DesignElement
import Controller
import Interface


""" Generates ANSI-C files from the given Abstract Syntax Tree
"""
class GeneratorANSIC:
    def __init__(self, ast):
        self._ast = ast
