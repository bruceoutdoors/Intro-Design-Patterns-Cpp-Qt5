#include "propertyselectormodel.h"
#include "propertyselectorview.h"
#include "propertyselectorcontrol.h"

#include <QApplication>
#include "audiometadata.h"

int main(int argc, char** argv) {
    QApplication qapp(argc, argv);
    AudioMetaData* sourceptr = new AudioMetaData();
    PropertySelectorControl* tchd = new PropertySelectorControl(sourceptr);
    tchd->show();
    return qapp.exec();
}
