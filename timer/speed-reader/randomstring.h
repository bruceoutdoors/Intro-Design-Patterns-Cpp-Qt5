#ifndef RANDOMSTRING_H
#define RANDOMSTRING_H

#include <QString>

class RandomString
{
public:
    RandomString(int len = 0);

    QString generateString();
    QString generateString(int len);

    void setStringLength(int len);
    int getStringLenght();
    bool isMatch(QString responseStr);
    int numCorrectChars(QString responseStr);
private:
    int m_stringLength;
    QString m_randomString;
};

#endif // RANDOMSTRING_H
