#!/usr/bin/env python

# GNUArchitect

import xml.etree.ElementTree as et
import ASTBuilder


""" main routine
"""
def main():
    tree = et.parse('thermometer.xml')
    builder = ASTBuilder.ASTBuilder( tree.getroot() )


""" process entry
"""
if __name__ == '__main__':
    main()
