#!/usr/bin/env python

# We use xml.etree.ElementTree and xml.etree.Element to parse XML's
# Very simple. Each node or element in the xml file can be represented
# as an xml.etree.Element object. This object has various attributes
# 1) attrib - a dictionary of Attributes
# 2) text - value of the element
# 3) _children - a python sequence
# 4) tag - tag name
# 5) tail - an optional tail string -
#    can be any application specific python object
# lets see some examples
# u you ElementTree when you are working with the whold document
# (like reading/writing whole python files)
# and use Elemen when working with individual nodes.

import xml.etree.ElementTree as ET

if (__name__ == "__main__"):
    tree = ET.parse('file.xml')  # tree is of type ElementTree
    root = tree.getroot()  # root is of type Element
    print(type(root))
    print('Text', root.text)
    print('Attributes', root.attrib)
    print('TagName', root.tag)
    # iterate over the children
    for child in root:
        print('ChildTag', child.tag)
        print('ChildAttributes', child.attrib)
        print('\n')

    # print Element attributes
    # print(root.__dict__)
    # print(vars(root))

    # also children are nested and can be returned by the [] operator
    print(root[1][2].text)  # should print 59900

    # element.iter() will iterate over all children, their children and soon.
    # it can take an optional Tag element in which case, it will only
    # iterate over the elements whose tag equal tag passed as argument.
    for child in root.iter():
        print('ChildTag', child.tag)
        print('ChildAttributes', child.attrib)
        print('\n')

    # some other important functions
    # root.clear()  # will reset the element
    # print('Text', root.text)
    # print('Attributes', root.attrib)
    # print('TagName', root.tag)

    # get(key, default=None) - get attribute with name = key, or return default value if not found
    value = root.get('time', default='Not found')
    print(value)

    value = root[0].get('name', default='Not found')
    print(value)

    # element.items() - will give you (key, value) pair of attributes
    # IN ANY ORDER
    for key, value in root[0][4].items():
        print(key, value)

    # element.keys() - will give you attributes names
    # IN ANY ORDER
    for name in root[0][4].keys():
        print(name)

    # element.set() - set an attribute on an element
    # element.find(tag|path) - find subelement (children) with matching tag or path.
    # element.findall(tag|path) - find all subelements and return a list.
    # and many other methods.

    # lets increment the rank by one for each rank element and write to a new XML
    tree = ET.parse('file.xml')
    root = tree.getroot()
    for rank in root.iter('rank'):
        old_rank = int(rank.text)
        old_rank += 1
        rank.text = str(old_rank)
        rank.set('updated', 'yes')
    tree.write('file2.xml')
