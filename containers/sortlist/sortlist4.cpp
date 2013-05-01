#include <QList>
#include <QtAlgorithms>   // for qSort()
#include <QStringList>
#include <QDebug>

class CaseIgnoreString : public QString {
public:
    CaseIgnoreString(const QString& other = QString()) 
    : QString(other) {}
    bool operator<(const QString & other) const {
        return toLower() < other.toLower();
    }
    bool operator==(const QString& other) const {
        return toLower() == other.toLower();
    }
};

int main() {
    CaseIgnoreString s1("Apple"), s2("bear"),
                     s3 ("CaT"), s4("dog"), s5 ("Dog");

    Q_ASSERT(s4 == s5);
    Q_ASSERT(s2 < s3);
    Q_ASSERT(s3 < s4);

    QList<CaseIgnoreString> namelist;

    namelist << s5 << s1 << s3 << s4 << s2; /* Insert
        all items in an order that is definitely not sorted. */

    qSort(namelist.begin(), namelist.end());
    int i=0;
    foreach (const QString &stritr, namelist) {
        qDebug() << QString("namelist[%1] = %2")
                       .arg(i++).arg(stritr) ;
    }

    QStringList strlist;
    strlist << s5 << s1 << s3 << s4 << s2; /* The value
       collection holds QString but, if you add CaseIgnoreString, 
       a conversion is required. */

    qSort(strlist.begin(), strlist.end());
    qDebug() << "StringList sorted: " + strlist.join(", ");
    return 0;
}

