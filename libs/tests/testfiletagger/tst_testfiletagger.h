#ifndef TST_TESTFILETAGGER_H
#define TST_TESTFILETAGGER_H

#include <QtTest/QtTest>
#include "metadatavalue.h"

class TestFileTagger : public QObject
{
    Q_OBJECT

public:
    TestFileTagger();

public Q_SLOTS:
    void testCase1();
    void fetched(const MetaDataValue &mdv);
};




#endif // TST_TESTFILETAGGER_H
