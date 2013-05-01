#include "propertyselectormodel.h"
#include "propertyselectorview.h"
#include "propertyselectormv.h"
#include <mp3file.h>
#include <QApplication>
#include <QObject>
#include <QAction>
#include <QToolBar>
#include <QDebug>
//start id=constructor
PropertySelectorControl::PropertySelectorControl(DataObject* sourceptr) :
   QMainWindow(0), m_Chdm(new PropertySelectorModel(sourceptr)),
   m_Chdv(new PropertySelectorView(m_Chdm)) {
       m_Chdm->initializePropertyNames();
       m_Chdv->setParent(this);
       QToolBar* toolbar = new QToolBar("Actions", this);
       QAction* showAction = new QAction("Show", toolbar);
       showAction->setObjectName("Show");
       showAction->setEnabled(true);
       toolbar->addAction(showAction);
       QMainWindow::addToolBar(Qt::BottomToolBarArea, toolbar);
       connect(showAction, SIGNAL(triggered(bool)),
               this, SLOT(showWindow(bool)));
       connect(this, SIGNAL(readyShow()), 
               m_Chdm, SLOT(prepareShow()));
       connect(m_Chdm, 
               SIGNAL(readyRestore(QList<QPersistentModelIndex>)), 
               m_Chdv, 
               SLOT(restoreSelects(QList<QPersistentModelIndex>)));
       connect(m_Chdv, SIGNAL(selectionsMade(QModelIndexList)),
               m_Chdm, SLOT(updateSelects(QModelIndexList)));
       connect(m_Chdm, SIGNAL(readyCloseWindow(bool)),
               this, SLOT(outputSelects(bool)));
       connect(m_Chdm, SIGNAL(readyCloseWindow(bool)),
               m_Chdv, SLOT(closeWindow(bool)));
}
//end
void PropertySelectorControl::showWindow(bool) {
    m_Chdv->clearSelection();
    emit readyShow();
    m_Chdv->setVisible(true);
}

QString PropertySelectorControl::getSelectedPropertyNames() const {
    return (m_Chdm->getSelectedPropertyNames()).join("\n"); 
}

void PropertySelectorControl::outputSelects(bool) {
    qDebug() << getSelectedPropertyNames();
}


//start id=testcode
int main(int argc, char** argv) {
    QApplication qapp(argc, argv);
    Mp3File* sourceptr = new Mp3File;
    PropertySelectorControl* tchd = new PropertySelectorControl(sourceptr);
    tchd->show();
    return qapp.exec();
}
//end

