#ifndef TESTMETADATA_H
#define TESTMETADATA_H

#include <QWidget>
#include <QModelIndex>

#include "metadataloader.h"


class QFileSystemModel;
class QMediaPlayer;
namespace Ui {
    class TestMetaData;
}

class TestMetaData : public QWidget
{
    Q_OBJECT

public:
    explicit TestMetaData(QWidget *parent = 0);
    ~TestMetaData();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_listView_clicked(QModelIndex index);
    void fetched(MetaDataValue mdv);
private:
    Ui::TestMetaData *ui;
    Abstract::MetaDataLoader * m_mdl;
    QFileSystemModel *m_fileSystem;
    QMediaPlayer *m_player;
};

#endif // TESTMETADATA_H
