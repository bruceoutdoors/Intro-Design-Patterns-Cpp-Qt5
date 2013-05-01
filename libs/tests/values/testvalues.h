#ifndef TESTVALUES_H
#define TESTVALUES_H

#include <QtTest/QtTest>
#include <QObject>

class TestValues : public QObject {
    Q_OBJECT
private slots:
    void testPointerEncoding();
};

#endif        //  #ifndef TESTVALUES_H
