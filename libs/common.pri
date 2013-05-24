# CPPLIBS - the directory where your library will be compiled and accessed from:
# QTLIBS - place directory of Qt libraries folder

win32 {
    CPPLIBS=$$PWD/cpplibs
    QTLIBS=C:/Qt/Qt5.0.2/5.0.2/mingw47_32/lib

    isEmpty( QTLIBS ) {
        error("You need to define QTLIBS environment variable(Qt lib folder).")
    }
}

linux-g++ {
    CPPLIBS=$$PWD/cpplibsLINUX
 }

# common settings for testcases in libs
CONFIG += debug

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

# make sure CPPLIBS and QTLIBS is defined
isEmpty(CPPLIBS) {
    error("You should define CPPLIBS environment variable to point to this location.")
}

