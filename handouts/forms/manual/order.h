#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QDate>

class Order {
public:
    QString name() const {return m_name;}
    QDate dateAdded() const { return m_added; }
    int quantity() const {return m_quantity; }
    double price() const {return m_price;}

    QString toString() const;
    void setName(const QString &name) {m_name = name;}
    void setDateAdded(const QDate &added) {m_added = added;}
    void setQuantity(int qty) {m_quantity = qty;}
    void setPrice(double unitPrice) {m_price = unitPrice;}
private:
    QString m_name;
    QDate m_added;
    int m_quantity;
    double m_price;

};


#endif        //  #ifndef ORDER_H
