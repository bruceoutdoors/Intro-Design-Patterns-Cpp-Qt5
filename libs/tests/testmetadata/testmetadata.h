#ifndef TESTMETADATA_H
#define TESTMETADATA_H

#include <QtTest/QtTest>
#include <QtCore>

#include <metadatavalue.h>

/** Testcase for operator<< and >> and other operators of
     MetaDataValue, when used on QTextStream/DataStream,
     as well as libmetadata's ability to fetch metadata via phonon. */

class TestMetaData : public QObject {
    Q_OBJECT

public:
    TestMetaData();
private slots:
    void initTestCase();
    /** Perform metadata lookup on a directory of audio tracks */
    void testLookupLots();
    /** If errors were encountered while loading some of the tracks, 
        perform second test on them */
    void testBadFiles();
    /** Verify that the input streams can reconstruct the values that were sent to the
    output stream */
    void cleanupTestCase();
        
    void handleFetch(MetaDataValue mdv);
signals:
    void progress(int);
    void progressMax(int);
private:

    int m_max;
    QSet<QString> m_toFind;
    QList<QString> m_badFiles;

    QHash<QString, MetaDataValue> m_loaded;
    
    QFile m_binaryFile;
    QFile m_textFile;

    // Test TextStream    
    QTextStream m_ts;
    // Test DataStream
    QDataStream m_ds;
    
    
};

#endif

