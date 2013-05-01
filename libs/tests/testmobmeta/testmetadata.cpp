#include <QtGui>
#include <QMediaPlayer>
#include <QMediaContent>
#include "testmetadata.h"
#include "ui_testmetadata.h"
#include "testtracks.h"


#include <metadatawidget.h>

TestMetaData::TestMetaData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestMetaData)
{
    ui->setupUi(this);
    m_player = new QMediaPlayer(this);
    m_mdl = new Mobility::MetaDataLoader(qApp);
    m_fileSystem = new QFileSystemModel(this);
    QString td = testTracksDir();
    m_fileSystem->setRootPath(td);
    ui->listView->setModel(m_fileSystem);
    ui->listView->setRootIndex(m_fileSystem->index(td));
    connect (m_mdl, SIGNAL(fetched(MetaDataValue)),
             this, SLOT(fetched(MetaDataValue)));
}

TestMetaData::~TestMetaData()
{
    delete ui;
}

void TestMetaData::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TestMetaData::on_listView_clicked(QModelIndex index)
{
    QString fileName = m_fileSystem->filePath(index) ;
    m_mdl->get(fileName);
}

void TestMetaData::fetched(MetaDataValue mdv) {
    ui->metaDataWidget->display(mdv);
}

int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    TestMetaData tmd;
    tmd.show();
    return app.exec();
}
