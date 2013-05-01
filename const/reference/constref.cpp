#include <QtCore>

class Person {
public:
    void setNameV( QString newName) {
        newName += " Smith";                /* Changes a temporary that's
            about to be destroyed. */
        m_Name = newName;
    }
    void setNameCR( const QString& newName) {
//      newName += " Python";               /* Error: Can't change const&. */
        m_Name = newName;
    }
    void setNameR( QString& newName) {
        newName += " Dobbs";                /* Changes the original QString. */
        m_Name = newName;
    }
private:
    QString m_Name;
};

int main() {
    Person p;
    QString name("Bob");
    p.setNameCR(name);                      /* No temporaries are created. */ 
//  p.setNameR("Monty");                    /* Error: Cannot convert to a QString&. */
    p.setNameCR("Monty");                   /* char* converts to temporary
        and gets passed by const reference. */
    p.setNameV("Connie");                   /* Temporary QString #1 is created to
        convert char* to QString. Temporary #2 is created when it is
        passed by value. */
    p.setNameR(name);                       /* No temporaries are created. */
    qDebug() << name;         
}
