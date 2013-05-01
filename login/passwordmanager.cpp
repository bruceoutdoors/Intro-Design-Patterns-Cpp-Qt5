#include "passwordmanager.h"
#include <QString>
#include <QProcess>
#include <QFile>
#include <QRegExp>
#include <QTextStream>

const QString auth = "auth"; 

PasswordManager::PasswordManager() {
    
}

/* Greps through the password file for an encrypted password, 
   and returns it. */
QString PasswordManager::getPassword(QString userName) {
    QFile afile(auth);
    QString searchPattern("^");
    searchPattern += userName + ":(.*)";
    QRegExp pattern(searchPattern);
     
    if (!afile.exists()) return false;
    afile.open(QIODevice::ReadOnly);
    
    QTextStream ifstream(&afile);
    QString inputLine = ifstream.readLine();
    while (!inputLine.isEmpty()) {
        if (pattern.exactMatch(inputLine)) 
            return pattern.capturedTexts()[1];
        inputLine = ifstream.readLine();
    }
    return QString();
}       
    

bool PasswordManager::checkPassword(QString userName, QString password) {
    QStringList argv;
    argv << "-nbs" << userName << password;
    start("htpasswd", argv);
    waitForReadyRead(2000);
    QByteArray bytes = readAllStandardOutput();
    if (bytes.length() < 1) return  false;
    QStringList lines = QString(bytes).split(":", QString::SkipEmptyParts);
    QString name = lines.takeFirst();
    QString shapw = lines.takeLast().trimmed();
    QString pw = getPassword(name);
    return  (pw != QString() && pw == shapw);
}

bool PasswordManager::addUser(QString userName, QString password) {
    if (getPassword(userName) != QString()) return false;
    setPassword(userName, password);
    return true;
}

void PasswordManager::setPassword(QString userName, QString password) {
    QStringList argv;
    argv << "-bs" << auth << userName << password;
    start("htpasswd", argv);
    QByteArray bytes = readAllStandardOutput();
    if (waitForFinished()) {
        terminate();     
    }
}

bool PasswordManager::changePassword(QString userName, QString oldPw, QString newPw) {
    if (checkPassword(userName, oldPw))  {
        setPassword(userName, newPw);
        return true;
    }
    return false;
}

