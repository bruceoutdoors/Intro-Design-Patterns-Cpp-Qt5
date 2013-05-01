#include <QCoreApplication>
#include <QTextStream>
#include <QProcess>
#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <cstdlib>

class Fork : public QProcess {
    public:
    Fork(QStringList argv = QStringList() ) {
        execute("environment", argv); /* Runs this same app as a child. */
    }
    ~Fork() {
        waitForFinished();
    }
};

QTextStream cout(stdout);
int main(int argc, char* argv[]) {

    QCoreApplication qca(argc, argv);
    QStringList al = qca.arguments();
    al.removeAt(0);
    bool fork=al.contains("-f");
    if(fork) {
       int i = al.indexOf("-f");
       al.removeAt(i);
    }

    QStringList extraVars;
    if (al.count()  > 0) {
        setenv("PENGUIN", al.first().toAscii(), true);
    }
    cout << " HOME=" << getenv("HOME") << endl;
    cout << " PWD=" << getenv("PWD") << endl;
    cout << " PENGUIN=" << getenv("PENGUIN") << endl;
    
    if (fork) {
        Fork f;   
    }
}

