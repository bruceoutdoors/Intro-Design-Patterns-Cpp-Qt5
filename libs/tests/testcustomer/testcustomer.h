#ifndef TESTCUSTOMER_H
#define TESTCUSTOMER_H
#include <QObject>
#include <QtTest/QtTest>

class TestCustomer : public QObject {
    Q_OBJECT
private slots:
    void test();

};


#endif
