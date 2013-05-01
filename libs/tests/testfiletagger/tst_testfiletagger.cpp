#include <QtGui>
#include "metadatavalue.h"
#include "testtracks.h"
#include "tmetadataloader.h"
#include "metadataloaderprogresswidget.h"
#include "tst_testfiletagger.h"

TestFileTagger::TestFileTagger()
{
    qApp->setApplicationName("testfiletagger");
    qApp->setOrganizationName("objectlearning.net");
}

void TestFileTagger::fetched(const MetaDataValue &mdv) {
    QTextStream cout(stdout);
    cout << mdv << endl;
}

void TestFileTagger::testCase1()
{
//    char* argv[] = {"testfiletagger"};
//    int argc = 1;
//    QApplication app(argc, argv);
    QTextStream cout(stdout);
    TagLib::MetaDataLoader* mdl = TagLib::MetaDataLoader::instance();
//    MetaDataFunctor f;
    /* MetaDataLoaderProgressWidget *progressWidget = new MetaDataLoaderProgressWidget(mdl);
    QDialog dialog;
    QHBoxLayout *hbox = new QHBoxLayout;
    dialog.setLayout(hbox);
    hbox->addWidget(progressWidget); */

    // progressWidget->show();
    QProgressDialog dialog;
    connect (mdl, SIGNAL(progressRangeChanged(int,int)),
             &dialog, SLOT(setRange(int,int)));
    connect (mdl, SIGNAL(progressValueChanged(int)),
             &dialog, SLOT(setValue(int)));
    connect (mdl, SIGNAL(fetched(MetaDataValue)),
             this, SLOT(fetched(MetaDataValue)));
    connect (mdl, SIGNAL(finished()), &dialog, SLOT(close()));

    QDirIterator qdi(testTracksDir(),
            QStringList() << "*.mp3",
            QDir::NoSymLinks | QDir::Files,
            QDirIterator::Subdirectories );
    int count = 0;
    while (qdi.hasNext()) {
        QString n = qdi.next();
        count ++;
        mdl->get(n);
    }
    dialog.setRange(0, count);
    dialog.exec();
}

// QTEST_APPLESS_MAIN(TestFileTagger);
int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    qRegisterMetaType<MetaDataValue>("MetaDataValue");
    TestFileTagger tf;
    qApp->setQuitOnLastWindowClosed(true);
    tf.testCase1();
    // return qApp->exec();
}



