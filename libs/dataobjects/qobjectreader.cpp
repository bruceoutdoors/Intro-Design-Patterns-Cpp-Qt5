#include <QFile>
#include <QVariant>
#include <QMetaProperty>
#include <QDebug>
#include <QTextStream>
#include <QXmlInputSource>
#include <QXmlSimpleReader>

#include "objectfactory.h"
#include "qobjectreader.h"



//start id=setup
QObjectReader::QObjectReader(QString filename, AbstractFactory* factory)
: m_Factory(factory), m_Current(0) {
    parseFile(filename);
    if (m_Factory == 0) m_Factory = new ObjectFactory();
}

void QObjectReader::parseFile(QString filename) {
     if (!QFile::exists(filename)) {
         qDebug() << "XMLIMPORT: unable to open " << filename;
         return;
     }
    QFile xmlFile(filename);
    QXmlInputSource source( &xmlFile );
    QXmlSimpleReader reader;
    reader.setContentHandler( this );
    reader.parse( source );
}

void QObjectReader::parse(QString text) {
    QXmlInputSource source;
    source.setData(text);
    QXmlSimpleReader reader;
    reader.setContentHandler(this);
    reader.parse(source);
}
//end

//start id=startelement
bool QObjectReader::startElement( const QString&,
     const QString& elementName, const QString&,
     const QXmlAttributes& atts) {              /* No need to name unused parameters. */
    if (elementName == "object") {
        if (m_Current != 0)                     /* If already inside a <object>, */
            m_ParentStack.push(m_Current);      /* push previous current onto stack. */
        QString classname = atts.value("class");
        QString instancename = atts.value("name");
        m_Current = m_Factory->newObject(classname);
        m_Current->setObjectName(instancename);
        if (!m_ParentStack.empty()) {           /* Top of parentstack, or previous current, should be my parent. */           
            m_Current->setParent(m_ParentStack.top());
        }
        return true;
    }
    if (elementName == "property") {
        QString fieldType = atts.value("type");
        QString fieldName = atts.value("name");
        QString fieldValue = atts.value("value");
        QVariant qv = QVariant(fieldValue);
        m_Current->setProperty(fieldName.toAscii(), qv);

    }
    return true;
}
//end
//start id="endelement"
bool QObjectReader::endElement( const QString& ,
                            const QString& elementName,
                            const QString& ) {
    if (elementName == "object") {
        if (!m_ParentStack.empty())
            m_Current = m_ParentStack.pop();
        else {
            addCurrentToQueue();
        }
    }
    return true;
}
//end

QObject* QObjectReader::getRoot() {
    if (m_ObjectList.isEmpty()) return 0;
    return m_ObjectList.dequeue();
}

bool QObjectReader:: endDocument() {
    //  qDebug() << "End of XML Document";
    return true;
}


void QObjectReader::addCurrentToQueue() {
    //  qDebug() << "Added Object to Queue";
    if (m_Current != 0) {
        m_ObjectList.enqueue(m_Current);
        m_Current = 0;
    }
}


QObjectReader::~QObjectReader() {}

