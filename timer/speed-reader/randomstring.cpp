#include <QDateTime>
#include "randomstring.h"

RandomString::RandomString(int len)
    :m_stringLength(len), m_randomString(QString()) {
    QDateTime dt = QDateTime::currentDateTime();
    qsrand(dt.toTime_t());
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
    const int CHARSETSIZE(26);
    const char FIRSTCHAR('a');
    m_randomString = "";
    for(int i = 0; i < len; i++){
        QChar randChar = FIRSTCHAR + qrand() % CHARSETSIZE;
        m_randomString.append(randChar);
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
