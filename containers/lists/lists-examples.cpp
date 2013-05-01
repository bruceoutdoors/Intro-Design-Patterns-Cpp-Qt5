#include <QStringList>
#include <QDebug>

/* Some simple examples using QStringList, split and join */

int main() {

    QString winter = "December, January, February";
    QString spring = "March, April, May";
    QString summer = "June, July, August";
    QString fall = "September, October, November";

    QStringList list;
    list << winter;                            /* Append operator 1. */
    list += spring;                            /* Append operator 2. */
    list.append(summer);                       /* Append member function. */
    list << fall;

    qDebug() << "The Spring months are: " << list[1] ;


    QString allmonths = list.join(", ");       /* From list to string - join with a ", " delimiter. */
    qDebug() << allmonths;

    QStringList list2 = allmonths.split(", "); /* Split is the opposite of join. Each month will have its own element. */

    Q_ASSERT(list2.size() == 12);              /* Q_ASSERTions abort the program if the condition is not satisfied. */

    foreach (const QString &str, list) {       /* Qt foreach loop - similar
      to Perl/Python and Java 1.5  style for loops. */
        qDebug() << QString(" [%1] ").arg(str);
    }

    for (QStringList::iterator it = list.begin();
         it != list.end(); ++it) {             /* C++ STL-style iteration. */
        QString current = *it;                 /* Pointer-style dereference. */
        qDebug() << "[[" << current << "]]";
    }

    QListIterator<QString> itr (list2);        /* Java 1.2 style Iterator. */
    while (itr.hasNext()) {                    /* Java Iterators point between elements. */
        QString current = itr.next();
        qDebug() << "{" <<  current << "}";
    }
    return 0;
}

