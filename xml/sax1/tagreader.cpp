#include "myhandler.h"
#include <QFile>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include <QDebug>

int main( int argc, char **argv ) {
    if ( argc < 2 ) {
        qDebug() << QString("Usage: %1 <xmlfiles>").arg(argv[0]);
        return 1;
    }
    MyHandler handler; 
    QXmlSimpleReader reader;                /* The generic parser. */
    reader.setContentHandler( &handler );   /* Hook the objects together. */
    for ( int i=1; i < argc; ++i ) {
        QFile xmlFile( argv[i] );
        QXmlInputSource source( &xmlFile );
        reader.parse( source );             /* Start parsing. */
    }
    return 0;
}
