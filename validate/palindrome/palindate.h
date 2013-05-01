#include <QValidator>
#include <QString>

class Palindate : public QValidator {
   Q_OBJECT
public:
   explicit Palindate(QObject* parent = 0);
   QValidator::State validate(QString& input, int&) const;
};

