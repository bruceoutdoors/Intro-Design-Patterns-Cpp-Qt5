#!/usr/bin/env python

if __name__ == "__main__" :
    from tagwrapper import *
    import filevisitor
    import os
    from os.path import *
    import sys

    path = "images"
    if len(sys.argv) > 1:
        path = argv[1]
    filename = "cards2.qrc"
    f = open(filename, "w")
    header = """<!DOCTYPE RCC>
"""
    f.write(header);
    resources = []
    for fn in filevisitor.listfiles(path, '*.png'):
#        name, ext = splitext(basename(fn))
        file = ["file", {"alias" : fn } , [fn], None]
        resources.append(file)
        resources.append("\n");
    qresource = ["qresource", None, resources, None]
    rcc = ["RCC", {"version": "1.0"}, [qresource, "\n"], None]
    f.write(toxml(rcc))
    f.close()
