#include "myhandler.h"
#include <QString>
#include <QTextStream>
//start
QTextStream cout(stdout);

bool MyHandler::startDocument() {
    indent = "";
    return TRUE;
}

bool MyHandler::characters(const QString& text) {
    QString t = text;
    cout << t.remove('\n');
    return TRUE;
}

bool MyHandler::startElement( const QString&, /* We have omitted the names of the parameters that we don't use. This prevents the compiler from issuing "unused parameter" warnings. */
                             const QString&, const QString& qName, 
                             const QXmlAttributes& atts) {
    QString str = QString("\n%1\\%2").arg(indent).arg(qName);
    cout << str;
    if (atts.length()>0) {
        QString fieldName = atts.qName(0);
        QString fieldValue = atts.value(0);
        cout << QString("(%2=%3)").arg(fieldName).arg(fieldValue);
    }
    cout << "{";
    indent += "    ";
    return TRUE;
}

bool MyHandler::endElement( const QString&,
    const QString& , const QString& ) {
    indent.remove( 0, 4 );
    cout << "}";
    return TRUE;
}
//end

