#include "docbookwalker.h"
#include <QDebug>

DocbookWalker::DocbookWalker(DocbookDoc doc) 
    :  m_document(doc), m_chapt(0), m_appendix(0), m_visited(0) {

}
  
void DocbookWalker::newSection(Element e, int depth) {
    m_currentSection = e;
    while (m_sectNum.size() < depth+2)
        m_sectNum << 0;
    ++m_sectNum[depth];
    m_sectNum[depth+1] = 0;
}


QString DocbookWalker::heading(Element sect) const {
    if (m_chapt == 0) return QString();
    QStringList sl;
    for (int i=0; i<m_sectNum.size(); ++i) {
        if (m_sectNum[i] > 0) 
            sl << QString("%1").arg(m_sectNum[i]);
    }
    QString header = sect.tagName();  
    if (header == "chapter") {
        sl.clear();
        sl << QString("%1").arg(m_chapt);
    }
    else if (header == "appendix") {
        QChar appendix('A' + (char) m_appendix);
        sl.insert(0, QString("%1").arg(appendix)); 
    }

    header[0] = header[0].toUpper();
    QString retval = header + " " + sl.join(".");
    QString titleString = m_document.getTitle(sect);
    retval += ": " + titleString;
    return retval;
}


QString DocbookWalker::currentHeading() const {
    return heading(m_currentSection);
}

void DocbookWalker::newChapter(Element e) {
    ++m_chapt;
    m_sectNum.clear();
    m_sectNum << m_chapt;
    m_currentChapter = e;
    m_currentSection = e;
}

void DocbookWalker::newAppendix(Element e) {
    ++m_appendix;
    m_sectNum.clear();
    m_currentChapter = e;
    m_currentSection = e;
    
}

bool DocbookWalker::visit(int depth, Element e) 
{
    QString name = e.tagName();
    if (name == "appendix") {
        newAppendix(e);
    }
    if (name == "chapter") {
        newChapter(e);
    }
    if (name == "section") {
        newSection(e, depth);
    }
    return true;
}


QDomNode DocbookWalker::walkTree(int depth, QDomNode current) {
    
    static int count = 0;
    ++count;
    if (count % 1000 == 0) qDebug() << "." << flush;
    bool checkChildren = false;    
    if (current.nodeType() == QDomNode::ElementNode) {
        Element ce = current.toElement(); 
        checkChildren = visit(depth, ce);
        ++m_visited;
    }
    if (checkChildren) {
        Element child = current.firstChildElement();
        while (!child.isNull()) {
            walkTree(depth+1, child); 
            child = child.nextSiblingElement();
        }
    }
    return current;
}


QDomDocument DocbookWalker::transform() {
    walkTree(0, m_document.documentElement());
    return m_document;
}
