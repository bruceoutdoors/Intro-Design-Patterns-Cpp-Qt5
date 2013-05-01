#include <QTextStream>
#include <QCoreApplication>
#include <QStringList>

int main (int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream cout(stdout);
    QStringList arglst = app.arguments();
    cout << "argc = " << argc << endl;
    for (int i=0; i<arglst.size(); ++i) {
        cout << QString("argv#%1 is %2").arg(i).arg(arglst[i]) << endl;
    }
    int num = arglst[argc - 1].toInt();
    cout << num * 2 << endl;
}

