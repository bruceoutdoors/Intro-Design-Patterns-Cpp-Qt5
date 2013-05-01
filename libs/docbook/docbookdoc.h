#ifndef DOCBOOKDOC_H
#define DOCBOOKDOC_H

#include "docbook_export.h"
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
//start id=typedef
typedef QDomElement Element; /* Saves on typing, and is
consistent with Java DOM. */
//end
   
/** A docbook/XML document
    @author Alan Ezust
	
*/   
class DOCBOOK_EXPORT DocbookDoc : public QDomDocument {
   public:
    DocbookDoc(QString title);

    /** @return a new <title> element with parent set to
       parent. */
    Element title(QString title, Element parent = Element());
    
    /** @return a new bridgehead element  child */
    Element bridgehead(QString title);
    
    Element orderedlist();
        
    
    /** @return a new <chapter> element, with given title,
       as a child of the root element */
    Element chapter(QString title);
   
    /**
     @return a simple xref element */
    Element xref(QString id) ;
    /** @return an xref in parantheses in a para */
    Element xrefP(QString id) ;
    
    /** @return a new section, as a child of the most
       recently created chapter.  */
    Element section(QString title);
    
    /** @return a new appendix */
    Element appendix(QString title);
    
    /** @return a parentless but of bold text */
    Element bold(QString boldText);

    Element listitem();
    
    /** @return the title of the corresponding element, 
        if there is one. */
    QString getTitle(Element el) const;
    
    /** @return a new paragraph with a title, as a child of the
        most recently created chapter or section */
    Element formalpara(QString title, QString text);
    /** @return an ordinary paragraph */
    Element para(QString text);
    
    /** @return a titled simplesect element */
    Element simplesect(QString titleStr) ;
    
    /** @param el An element for which you want to set an
    attribute
        @param role - the condition you wish to set
    */
    static void setRole(Element el, QString role); 

    Element currentParent; /* All new paragraphs go under this
    parent */

    Element currentPara;
    
    Element currentChapter; /* All new sections go under this */
    
    Element currentList; /* All new ListItems go under this */
};

inline Element& operator<<(Element& parent, QDomNode newChild) {
    parent.appendChild(newChild);
    return parent;
}


#endif        //  #ifndef DOCBOOKDOC_H
