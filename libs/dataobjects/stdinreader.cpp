#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QDebug>

#include "stdinreader.h"

static QTextStream cout(stdout);
static QTextStream cin(stdin);
static QTextStream cerr(stderr);

bool StdinReader::readProperties(DataObject* doptr) {
    const QMetaObject* meta = doptr->metaObject();

    cout << QString(" readFromStandardInput<%1>(): ").arg(doptr->className()) << endl;
    for (int i=0; i < meta->propertyCount(); ++i) {
        QMetaProperty mp = meta->property(i);

        // Special case for the property "name" of QObject, which we wish to skip
        if (QString("name") == mp.name())
            continue;

        QString prompt = QString( "[%1] %2: ").arg( mp.type() ).arg( mp.name());
        bool done=false;
        do {
            // qDebug() << QString("ValidInputs: %1").arg(doptr->validInputs(mp.name()));
            cout << prompt;
            QString inpline = cin.readLine();
            QVariant qv(inpline);

            // it seems that QObject::setProperty() will sometimes return true even if the
            // value is invalid. Therefore, we must also check the QVariant's isValid() method.
            if (doptr->setProperty(mp.name(), qv) &&  doptr->property(mp.name()).isValid()) {
                done=true;
            } else {
				cout << "Invalid input - please try again." << endl;
//                cout() << doptr->validInputs(mp.name()) << endl;
            }
        } while (!done);
    }
    return true;
}
