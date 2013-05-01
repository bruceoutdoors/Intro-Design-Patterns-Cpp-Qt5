#include <QtGui>
#ifdef USE_TAGLIB
#include "tmetadataloader.h"
#else
#include "metadataloader.h"
#endif
#include "testmetadata.h"
#include "ui_testmetadata.h"
#include "testtracks.h"

TestMetaData::TestMetaData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestMetaData)
{
    ui->setupUi(this);
    m_fileSystem = new QFileSystemModel(this);
    QString td = testTracksDir();
    m_fileSystem->setRootPath(td);
    ui->listView->setModel(m_fileSystem);
    ui->listView->setRootIndex(m_fileSystem->index(td));
#ifdef USE_TAGLIB
    m_mdl = TagLib::MetaDataLoader::instance();
#else    
    m_mdl = Phonon::MetaDataLoader::instance();
#endif
    connect (m_mdl, SIGNAL(fetched(MetaDataValue)), this, SLOT(gotData(MetaDataValue)));
}

TestMetaData::~TestMetaData()
{
    delete ui;
}

void TestMetaData::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TestMetaData::on_listView_activated(const QModelIndex &index)
{

}

void TestMetaData::gotData(const MetaDataValue &mdv) {
    m_mdo = mdv;
    ui->widget->display(mdv);
}

void TestMetaData::on_listView_clicked(QModelIndex index)
{
    QString fileName = m_fileSystem->filePath(index) ;
    m_mdl->get(fileName);
}
