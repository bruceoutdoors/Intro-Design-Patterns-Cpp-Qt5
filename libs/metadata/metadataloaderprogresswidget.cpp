#include <QtGui>
#include "abstractmetadataloader.h"
#include "metadataloaderprogresswidget.h"


MetaDataLoaderProgressWidget::MetaDataLoaderProgressWidget(Abstract::MetaDataLoader *mdl, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    setLayout(hbox);
    m_progressBar = new QProgressBar;
    m_progressBar->setTextVisible(true);
    m_cancelButton=new QToolButton();
    m_cancelButton->setIcon(QIcon(":/icons/cancel.png"));
    hbox->addWidget(m_cancelButton);
    hbox->addWidget(m_progressBar);
    
    if (mdl == 0) mdl = Abstract::MetaDataLoader::instance();
    hookup(mdl);
    setVisible(false);
}
void MetaDataLoaderProgressWidget::hookup(Abstract::MetaDataLoader* mdl) {
        
    connect (mdl, SIGNAL(progressRangeChanged(int,int)),
             this, SLOT(updateRange(int, int)), Qt::QueuedConnection);
    connect (mdl, SIGNAL(progressRangeChanged(int,int)),
             this, SLOT(show()), Qt::QueuedConnection);
    connect (mdl, SIGNAL(finished()),
             this, SLOT(hide()), Qt::QueuedConnection);

    connect (mdl, SIGNAL(progressValueChanged(int)),
             m_progressBar, SLOT(setValue(int)), Qt::QueuedConnection);
    connect (mdl, SIGNAL(progressRangeChanged(int,int)),
             m_progressBar, SLOT(setRange(int,int)), Qt::QueuedConnection);
    connect (m_cancelButton, SIGNAL(triggered(QAction*)),
             mdl, SLOT(cancel()));
    connect (mdl, SIGNAL(fetched(MetaDataValue)), this, SLOT(updateStatus(MetaDataValue)));
}

void MetaDataLoaderProgressWidget::updateStatus(const MetaDataValue &v) {
    lastValue = v;
}

void MetaDataLoaderProgressWidget::updateRange(int min, int max) {
    show();
    m_progressBar->setRange(min, max);
}
