#ifndef DOCBOOKWALKER_H
#define DOCBOOKWALKER_H
#include <QChar>
#include <QStringList>
#include "docbookdoc.h"
#include "docbook_export.h"

/** A class designed for traversing and transforming 
    Docbook Documents. Keeps track of section#s and chapter#s.
	@author Alan Ezust
 */
class DOCBOOK_EXPORT DocbookWalker {
 public:
    DocbookWalker(DocbookDoc doc);
    /** Traverses whole tree. */
    virtual QDomDocument transform();
    virtual ~DocbookWalker() {}
    /**
    @return number of nodes visited 
    */
    virtual int visited() const { 
        return m_visited; 
    } 
 protected:

    /** Visits the current Element.
        Handles elements like <chapter> <section> nd
        <appendix> for numbering purposes.

        Called from walkTree from transform.
        Not to be called pubclicly.
        
        You can override this, handle specific elements,
        and call the base class version for elements you
        do not handle.
    @param e the Element to visit
    @param depth the current depth of the tree
    @return false if we should not check the children after
            handling this object. 
    */
    virtual bool visit(int depth, Element e) ;

    /** @return For the current chapter/section/appendix, returns the element name followed by its number, and its title, as a QString. */
    QString currentHeading() const;
    
    /**
      @param sect a chapter, section or appendix 
      @return the heading string of sect. */
    QString heading(Element sect) const;

    QDomNode walkTree(int depth, QDomNode current);

    void newChapter(Element e);
    void newSection(Element e, int depth);
    void newAppendix(Element e) ;
    
    Element& currentChapter() {
        return m_currentChapter;
    }
    Element& currentSection() {
        return m_currentSection;
    }
    
    
 protected:
    mutable DocbookDoc m_document;


 private:
    Element m_currentChapter;
    Element m_currentSection;
    int m_chapt;
    int m_appendix;
    int m_visited;
    QList<int> m_sectNum;
};
#endif        //  #ifndef DOCBOOKWALKER_H
