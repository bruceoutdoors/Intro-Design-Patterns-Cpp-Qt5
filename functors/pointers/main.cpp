#include <QtGui>

QString name() {
    return QString("Alan");
}

typedef QString (*funcPtr)();               /* A function that returns QString and takes no args. */
Q_DECLARE_METATYPE(funcPtr);                /* Declare, so we can use in QVariant. */

int main() {
    qRegisterMetaType<funcPtr>("funcPtr");  /* Register, so we can use in queued signal parameters. */
    funcPtr ptr = name;                     /* Function names evaluate to pointers to functions. */

    QString v = (*ptr)();                   /* Invoke a method by dereferencing function ptr. */
    qDebug() << v << endl;                  /* Prints "Alan" */
}
