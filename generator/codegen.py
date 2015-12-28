#!/usr/bin/env python

import xml.etree.ElementTree as et
import Interface


""" Extracts the design from XML description
"""
class XMLParser:
    def __init__(self, root):
        self._root = root
        self.visitNode(root)

    def visitNode(self, root ):
        for child in root:
            print(child.tag, child.attrib)
            self.visitNode(child)



""" main routine
"""
def main():
    tree = et.parse('thermometer.xml')
    root = tree.getroot()
    parser = XMLParser( root )


""" process entry
"""

if __name__ == '__main__':
    main()
