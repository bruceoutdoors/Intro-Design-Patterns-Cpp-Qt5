template <class T>
class QSharedPointer {
public:
    QSharedPointer();
    explicit QSharedPointer(T* ptr);
    T& operator*() const;
    T* operator ->() const;

    bool isNull() const;
    operator bool() const;
    bool operator!() const;  
    // [ ... ]
};
