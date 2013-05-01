#ifndef MYHANDLER_H
#define MYHANDLER_H
//start
#include <QXmlDefaultHandler>
class QString;
class MyHandler : public QXmlDefaultHandler {
  public:
    bool startDocument();
    bool startElement( const QString & namespaceURI,
                       const QString & localName,
                       const QString & qName,
                       const QXmlAttributes & atts);
    bool characters(const QString& text);
    bool endElement( const QString & namespaceURI,
                     const QString & localName,
                     const QString & qName );
  private:
    QString indent;
};
//end

#endif        //  #ifndef MYHANDLER_H
