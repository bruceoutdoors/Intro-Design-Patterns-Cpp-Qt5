#include <QApplication>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QVariant>
#include <QDebug>
#include "fraction.h"
//start id="construct"
void createTest() {
    static int fracType = QMetaType::type("Fraction");
    void* vp = QMetaType::construct(fracType);
    Fraction* fp = reinterpret_cast<Fraction*>(vp); /* Note: This is our first
    use of reinterpret_cast in this book! */
    fp->first = 1;
    fp->second = 2;
    Q_ASSERT(*fp == Fraction(1,2));
}
//end
//start id="variantback"
int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    qRegisterMetaType<Fraction>("Fraction");
    Fraction twoThirds (2,3);
    QVariant var;
    var.setValue(twoThirds);
    Q_ASSERT (var.value<Fraction>() == twoThirds);

    Fraction oneHalf (1,2);
    Fraction threeQuarters (3,4);

    qDebug() << "QList<Fraction> to QVariant and back."

    QList<Fraction> fractions;
    fractions << oneHalf << twoThirds << threeQuarters;
    QFile binaryTestFile("testMetaType.bin");
    binaryTestFile.open(QIODevice::WriteOnly);
    QDataStream dout(&binaryTestFile);
    dout << fractions;
    binaryTestFile.close();
    binaryTestFile.open(QIODevice::ReadOnly);
    QDataStream din(&binaryTestFile);
    QList<Fraction> frac2;
    din >> frac2;
    binaryTestFile.close();
    Q_ASSERT(fractions == frac2);
    createTest();
    qDebug() << "If this output appears, all tests passed.";
}
//end

