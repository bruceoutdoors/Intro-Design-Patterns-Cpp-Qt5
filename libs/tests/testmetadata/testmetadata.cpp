#include <metadataloader.h>
#include "testmetadata.h"
#include "metadatavalue.h"
#include "testtracks.h"

#include <QProgressDialog>
#include <QDebug>


TestMetaData::TestMetaData()
    : m_binaryFile("playlist.bin"),
    m_textFile("playlist.tsv")
{
    qApp->setApplicationName("testmetadata");
    qApp->setOrganizationName("mcs.suffolk.edu");
    qRegisterMetaType<MetaDataValue>("MetaDataValue");
    qRegisterMetaType<MetaDataValue>("Preference");

}
void TestMetaData::initTestCase() {

    QVERIFY(m_textFile.open(QIODevice::WriteOnly));
    m_ts.setDevice(&m_textFile);
    QVERIFY(m_binaryFile.open(QIODevice::WriteOnly));
    m_ds.setDevice(&m_binaryFile);
    connect(Phonon::MetaDataLoader::instance(), SIGNAL(fetched(MetaDataValue)),
            this, SLOT(handleFetch(MetaDataValue)), Qt::QueuedConnection);
}

void TestMetaData::testLookupLots() {
    QProgressDialog dlg;
//    dlg.setAutoClose(false);
    dlg.setValue(0);
    connect (this, SIGNAL(progress(int)), &dlg, SLOT(setValue(int)), Qt::QueuedConnection);
    connect (this, SIGNAL(progressMax(int)), &dlg, SLOT(setMaximum(int)), Qt::QueuedConnection);

    QDirIterator it(testTracksDir(), QDirIterator::Subdirectories);
    
    while (it.hasNext()) {
        QString path = it.next();
        if (!path.endsWith(".mp3")) continue;
        Phonon::MetaDataLoader::instance()->get(path);
        m_toFind << path;
        ++m_max;
        // emit progressMax(++m_max);
    }
    dlg.setMaximum(m_max);
    if (m_toFind.size() > 0)
        dlg.exec();

    QFile f("badfiles.lst");

    if (f.open(QIODevice::WriteOnly)) {
        QTextStream ts(&f);
        foreach (const QString& s, m_toFind) {
            qDebug() << "badFile: " << s;
            ts << s << endl;
        }
    }
    QCOMPARE(m_toFind.size(), 0);
}

void TestMetaData::testBadFiles() {
    QFile f("badfiles.-test.lst");
    if (f.open(QIODevice::ReadOnly)) {
        QTextStream is(&f);
        QStringList files = is.readAll().split("\n");
        foreach (const QString &f, files) {
            if (f == QString()) continue;
            qDebug() << "tbf: " << f;
            MetaDataValue mdl;
            mdl = m_loaded[f];
            QVERIFY(!mdl.isNull());
            QVERIFY(mdl.fileName() != QString());
        }
    }
}



void TestMetaData::handleFetch(MetaDataValue mdv) {
    m_loaded[mdv.fileName()] = mdv;
    m_toFind.remove(mdv.fileName());
    // Writing out to tsv and binary
    m_ts << mdv;
    m_ds << mdv;
    emit progress(m_max - m_toFind.size());

}

void TestMetaData::cleanupTestCase() {
    m_textFile.close();
    m_binaryFile.close();
    QVERIFY(m_textFile.open(QIODevice::ReadOnly));
    m_ts.setDevice(&m_textFile);
    QVERIFY(m_binaryFile.open(QIODevice::ReadOnly));
    m_ds.setDevice(&m_binaryFile);
    // Read the files with the >> operators. 
    for (int i=m_loaded.size()-1; i >= 0; --i) {
        MetaDataValue fromText;
        MetaDataValue fromBinary;
        m_ts >> fromText;
        m_ds >> fromBinary;
        QVERIFY(equal(fromText, fromBinary));
        QVERIFY(equal(fromText, m_loaded[fromText.fileName()]));
    }
    qDebug() << "Number of files tested:" << m_loaded.size();
}


QTEST_MAIN(TestMetaData);
