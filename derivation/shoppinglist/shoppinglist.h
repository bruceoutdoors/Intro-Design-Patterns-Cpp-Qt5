#ifndef _SHOPPING_LIST_H_
#define _SHOPPING_LIST_H_

#include <QStringList>

class ShoppingList : public QStringList {
public:
    QStringList& operator<<(const QString& newItem);
    QString makePrintList();
private:
    static QString s_Check;
};

#endif
