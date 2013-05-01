#include <QString>
#include <QTextStream>
#include <QChar>
#include <QDate>

int main() {
    QTextStream cout(stdout);
    char array1[34] = "This is a dreaded C array of char";
    char array2[] = "if not for main, we could avoid it entirely.";
    char* charp = array1;                                       /* Pointer to first element of array. */
    QString qstring = "This is a unicode QString. Much preferred." ;
    Q_ASSERT (sizeof(i) == sizeof(int));
    cout << "  c type sizes: \n";
    cout << "sizeof(char) = " << sizeof(char) << '\n';
    cout << "sizeof(wchar_t) = " << sizeof(wchar_t) << '\n';
    cout << "sizeof(int) = " << sizeof(int) << '\n';
    cout << "sizeof(long) = " << sizeof(long) << '\n';
    cout << "sizeof(float) = " << sizeof(float) << '\n';
    cout << "sizeof(double) = " << sizeof(double) << '\n';
    cout << "sizeof(double*) = " << sizeof(double*) << '\n';
    cout << "sizeof(array1) = " << sizeof(array1) << '\n';
    cout << "sizeof(array2) = " << sizeof(array2) << '\n';
    cout << "sizeof(char*) = " << sizeof(charp) << endl;
    cout << "  qt type sizes: \n";
    cout << "sizeof(QString) = " << sizeof(QString) << endl;
    cout << "sizeof(qint32) = " << sizeof (qint32) << "\n";     /* Guaranteed to
        be 32 bits on all platforms. */
    cout << "sizeof(qint64) = " << sizeof(qint64) << '\n';      /* Guaranteed to
        be 64 bits on all platforms. */
    cout << "sizeof(QChar) = " << sizeof (QChar) << endl;       /* Twice as big
       as a char */
    cout << "sizeof(QDate) = " << sizeof(QDate) << endl; 
    cout << "qstring.length() = " << qstring.length() << endl;  /* For # of
        bytes, be sure to take into account the size of QChar. */
    return 0;
}
/*OUT 
(example run on 32-bit system)
sizeof(char) = 1
sizeof(wchar_t) = 4
sizeof(int) = 4
sizeof(long) = 4
sizeof(float) = 4
sizeof(double) = 8
sizeof(double*) = 4
sizeof(array1) = 34
sizeof(array2) = 45
sizeof(char*) = 4
  qt type sizes:
sizeof(QString) = 4
sizeof(qint32) = 4
sizeof(qint64) = 8
sizeof(QChar) = 2
sizeof(QDate) = 4
qstring.length() = 42
*/
