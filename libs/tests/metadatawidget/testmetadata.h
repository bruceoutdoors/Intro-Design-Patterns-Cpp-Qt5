#ifndef TESTMETADATA_H
#define TESTMETADATA_H
#include <QModelIndex>
#include <QDialog>
#include "metadataobject.h"
#include <QFileSystemModel>

namespace Ui {
    class TestMetaData;
}
namespace Abstract {
    class MetaDataLoader;
}
class TestMetaData : public QDialog
{
    Q_OBJECT

public:
    explicit TestMetaData(QWidget *parent = 0);
    ~TestMetaData();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_listView_activated(const QModelIndex &index);
    void gotData(const MetaDataValue& mdv);
    void on_listView_clicked(QModelIndex index);

private:
    Ui::TestMetaData *ui;
    QFileSystemModel *m_fileSystem;
    MetaDataObject m_mdo;
    Abstract::MetaDataLoader *m_mdl;
};

#endif // TESTMETADATA_H
