#include "abstractmetadataloader.h"
#include <QtCore>

using namespace Abstract;

MetaDataLoader* MetaDataLoader::instance() {
    MetaDataLoader* retval =
            qApp->findChild<MetaDataLoader*>();
    if (retval == 0) {
       qCritical() << "Abstract::MetaDataLoader::instance(): "
                    "Create concrete derived MetaDataLoader before calling this.";
       Q_ASSERT(false);
    }
    return retval;
}
MetaDataLoader::~MetaDataLoader() {
}
