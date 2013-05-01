# common settings for testcases in libs
CONFIG += debug

CPPLIBS=$$(CPPLIBS)
isEmpty( CPPLIBS ) {
    error("You need to define CPPLIBS environment variable.")
}

# place executable in same directory (not a debug/ or release/ folder)
app {
   DESTDIR=$$OUT_PWD
}

# place auto-generated files in "invisible" subdirectories
win32 {
    MOC_DIR = _moc
    OBJECTS_DIR = _obj
    # place executable in current directory
} else {
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}

# don't place executables in an app bundle on mac os
mac {
    CONFIG -= app_bundle
}

LIBS += -L$$(CPPLIBS)
