#ifndef _STACK_H_
#define _STACK_H_

#include <QList>

template<class T>
class Stack : private QList<T> { 
public:
    bool isEmpty() const {
        return QList<T>::isEmpty();
    }
    T pop() {
        return takeFirst();
    }
    void push(const T& value) {
        prepend(value);
    }
    const T& top() const {
        return first();
    }
    int size() const {
        return QList<T>::size();
    }
    void clear() {
        QList<T>::clear();
    }
};
#endif

