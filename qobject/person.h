#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>
//start

class Person : public QObject {
 public:
    explicit Person(QString name, QObject* parent = 0);
    virtual ~Person();
};
//end

#endif
