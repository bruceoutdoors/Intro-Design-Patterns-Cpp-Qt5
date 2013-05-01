#ifndef DATAOBJECTREADER_H
#define DATAOBJECTREADER_H

//start
#include "dobjs_export.h"
#include <QString>
#include <QStack>
#include <QQueue>
#include <QXmlDefaultHandler>

class AbstractFactory;

/** Parses XML and returns QObject trees. 
 This class permits the importing of data from an
 XML file, and creates a queue of dynamically allocated
 QObjects, returning them one at a time through
 importInstance(). Parent-child relationships are maintained,
 and the properties are set as according to the input specification.
 @author Alan Ezust
 
*/
class DOBJS_EXPORT  QObjectReader : public QXmlDefaultHandler {
  public:
    /**
     parses the file and stores a list of the objects
     internally, which can be obtained from
     @ref importInstance()
     @param factory the objectfactory you wish to use
     when an <object> tag is encountered.
     Defaults to one which only creates
     @ref PropsMap instances to hold your properties.
    */
    explicit QObjectReader (AbstractFactory* factory=0) : 
                         m_Factory(factory), m_Current(0) { }
    explicit QObjectReader (QString filename, AbstractFactory* factory=0);
    void parse(QString text);
    void parseFile(QString filename);
    /**
        @return the root xml object, if there is one.
        NULL if there is not. 
        If this represents an element with child-elements,
        the child-elements are returned as its children.
    */
    QObject* getRoot();
    ~QObjectReader();

    // callback methods from QXmlDefaultHandler
    bool startElement( const QString& namespaceURI,
                       const QString& name,
                       const QString& qualifiedName,
                       const QXmlAttributes& attributes );
    bool endElement(  const QString& namespaceURI,
                      const QString& localName,
                      const QString& qualifiedName);
    bool endDocument();
  private:
    void addCurrentToQueue();
    AbstractFactory* m_Factory;
    QObject* m_Current;
    QQueue<QObject*> m_ObjectList;
    QStack<QObject*> m_ParentStack;
};
//end

#endif        //  #ifndef DATAOBJECTREADER_H
