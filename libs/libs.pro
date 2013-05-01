CPPLIBS=$$(CPPLIBS)
isEmpty(CPPLIBS) {
    error("You should define CPPLIBS environment variable to point to this location.")
}

TEMPLATE = subdirs
# Process directories in order (some are dependent on others):
CONFIG += ordered

SUBDIRS += dataobjects \
           metadata \
           actioneditor \
           icons \
           phononmetadata \
           sqlmetadata \
           docbook \
           cards2 \
           customer \
           objectbrowser


OTHER_FILES += README.txt

# Optional taglib based metadataloader.
USE_TAGLIB=$$(USE_TAGLIB)
!isEmpty(USE_TAGLIB) {
    DEFINES += USE_TAGLIB
    SUBDIRS += filetagger
}

SUBDIRS += tests
