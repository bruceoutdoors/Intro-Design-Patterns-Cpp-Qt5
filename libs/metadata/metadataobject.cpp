#include "metadataobject.h"

void MetaDataObject::setUrl(QUrl url) {
    SUPER::setUrl(url);
    setObjectName(fileName());
}

MetaDataObject& MetaDataObject::operator=(const MetaDataValue& other) {
	SUPER::operator=(other);
	return *this;
}

MetaDataObject& MetaDataObject::operator=(const MetaDataObject& other) {
	SUPER::operator=(other);
	return *this;
}
