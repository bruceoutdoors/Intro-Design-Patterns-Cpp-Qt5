#include "propertyselectormodel.h"
#include "propertyselectorview.h"
#include "propertyselectorcontrol.h"

int main(int argc, char** argv) {
    QApplication qapp(argc, argv);
    Mp3File* sourceptr = new Mp3File;
    PropertySelectorControl* tchd = new PropertySelectorControl(sourceptr);
    tchd->show();
    return qapp.exec();
}
