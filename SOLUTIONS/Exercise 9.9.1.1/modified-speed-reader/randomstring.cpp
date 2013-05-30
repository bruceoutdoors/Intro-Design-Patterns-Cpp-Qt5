#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include "randomstring.h"

RandomString::RandomString(int len, QString dictionary)
    :m_stringLength(len), m_randomString(QString()) {
    QDateTime dt = QDateTime::currentDateTime();
    qsrand(dt.toTime_t());

    QFile file(dictionary);

    // warns user if can't find a file
    Q_ASSERT_X(file.open(QIODevice::ReadOnly | QIODevice::Text),
               "reading file", QString("can't open %1").arg(dictionary).toLatin1());

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if(line != "")
            m_dictWords.append(line);
    }
}

void RandomString::setStringLength(int len) {
    m_stringLength = len;
}

int RandomString::getStringLenght() {
    return m_stringLength;
}

QString RandomString::generateString() {
    return generateString(m_stringLength);
}

QString RandomString::generateString(int len) {
    m_randomString = "";

    int randNum;
    for(int i = 0; i < len; i++) {
        randNum = qrand() % m_dictWords.count();
        m_randomString.append(m_dictWords[randNum]);
    }

    return m_randomString;
}

bool RandomString::isMatch(QString responseStr) {
    return (responseStr.compare(m_randomString)==0) ;
}

int RandomString::numCorrectChars(QString responseStr) {
    int numCorrect = 0;
    int totalNum = responseStr.count();
    if(totalNum >= m_randomString.count())
        totalNum = m_randomString.count();
    for(int i=0; i< totalNum;i++){
        if(responseStr.at(i)== m_randomString.at(i))
            numCorrect++;
    }
    return numCorrect;
}
