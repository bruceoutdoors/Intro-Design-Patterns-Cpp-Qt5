TEMPLATE=subdirs
SUBDIRS = assert\
          testactioneditor\
          testcustomer \
	  testicons \
          xmlimport \
          preference \
          properties \
          values  
# optional subdirs
SUBDIRS += testmetadata \
           testsqlmetadata \
           metadatawidget

USE_TAGLIB=$$(USE_TAGLIB)
!isEmpty(USE_TAGLIB) {
	SUBDIRS += testfiletagger  
}


