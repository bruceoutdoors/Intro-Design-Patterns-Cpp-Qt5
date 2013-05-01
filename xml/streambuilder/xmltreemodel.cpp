#include "xmltreemodel.h"
#include <QDebug>
#include <QStandardItem>
#include <QFile>

XmlTreeModel::XmlTreeModel(QObject *parent) :
    QStandardItemModel(parent),
    m_currentItem(0) {
}

//start
void XmlTreeModel::open(QString fileName) {
    QFile file (fileName);                                /* Closes automatically when out of scope. */    
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't open file: " << fileName;
        abort();
    }
    m_streamReader.setDevice(&file);                      /* Start parsing - can use any QIODevice. */
    while (!m_streamReader.atEnd()) {
        QXmlStreamReader::TokenType tt = m_streamReader.readNext();
        switch (tt) {
            case QXmlStreamReader::StartElement: {
                QString name = m_streamReader.name().toString();
                QStandardItem* item = new QStandardItem(name);
                item->setData(m_streamReader.lineNumber(), 
                              LineStartRole);             /* Custom data() */
                QXmlStreamAttributes attrs = m_streamReader.attributes();
                QStringList sl;
                sl << tr("Line# %1").arg(m_streamReader.lineNumber());
                foreach (QXmlStreamAttribute attr, attrs) {
                    QString line = QString("%1='%2'").arg(attr.name().toString())
                                    .arg(attr.value().toString());
                    sl.append(line);
                }
                item->setToolTip(sl.join("\n"));
                if (m_currentItem == 0) 
                   setItem(0, 0, item);                   /* Set root item in model. */
                else 
                   m_currentItem->appendRow(item);        /* Add as a child to the current item. */
                m_currentItem = item;
                break; }
            case QXmlStreamReader::Characters: {
                QString tt = m_currentItem->toolTip();
                tt.append("\n");
                tt.append(m_streamReader.text().toString());
                m_currentItem->setToolTip(tt);
                break; }
            case QXmlStreamReader::EndElement: 
                m_currentItem->setData(m_streamReader.lineNumber(), LineEndRole);
                m_currentItem = m_currentItem->parent();  /* Go up the tree. */
                break;
            case QXmlStreamReader::EndDocument:
            default:
                break;
        }
    }
}

