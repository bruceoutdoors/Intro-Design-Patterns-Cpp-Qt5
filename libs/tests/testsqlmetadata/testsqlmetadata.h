#ifndef TESTSQLMETADATA_H
#define TESTSQLMETADATA_H


#include <QObject>
#include <QtTest/QtTest>
class QProgressDialog;
#include "metadatavalue.h"
/* Testcase for libSqlMetaData */

class TestSqlMetaData : public QObject
{
Q_OBJECT
private slots:
    void initTestCase();
    void testVisit();    // adds to metadata
    void testAddLots();  // adds to a playlist
    void testPlayList();  // drops and re-adds to playlist
    void showTable();    // shows a QTableView with a QSqlTableModel
    // slot for tracking what's been fetched by metadataloader for later comparison
    void handleFetch(MetaDataValue mdv);

private:
    QString m_playListName;
    QProgressDialog *m_dialog;
    QStringList m_trackUrls;
    QMap<QString, MetaDataValue> m_fetched;

};



#endif        //  #ifndef TESTSQLMETADATA_H
