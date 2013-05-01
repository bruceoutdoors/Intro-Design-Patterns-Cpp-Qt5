#ifndef DomWalker_H
#define DomWalker_H

/**
  Another example of the Visitor Pattern -
  this class traverses a DOM tree.
*/
#include <QDomNode>
#include <QDomElement>
#include <QDomDocument>

/**
   DomWalker is a simple DOM Transformation
   class which permits the in-place modification
   of parsed XML trees. 
   
   You can override visit() as the operation for each XML Element,
   and then call transform() to get the 
   
   */

class DomWalker {
public:
    /**
      @param doc the document you wish to transform
    */

    DomWalker(QDomDocument doc);
    virtual ~DomWalker() {}

    /**
       Override this method to do something to the QDomElement as
       it's being visited. */

    virtual QDomElement visit(QDomElement current)=0;

    /**
    Calls visit() on every element.          
    */
    QDomDocument transform();

protected:
    QDomNode walkTree(QDomNode current);
    QDomElement createElement(QString name);
    QDomDocument m_Doc;

};


#endif        //  #ifndef DomWalker_H

