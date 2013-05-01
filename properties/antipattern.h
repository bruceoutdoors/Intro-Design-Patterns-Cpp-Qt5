
class Customer {
public:
    void setName(QString newName);
    void setAddress(QString newAddress);
    void setCity(QString newCity);
    void setBirthdate(const QDate& newDate);

    QString getName() const;
    QString getAddress() const;
    QString getCity() const;
    QDate getBirthdate() const;

    // Operations we wish to perform on this class
    void exportXML(ostream& os);
    void importXML(istream& is);
    QWidget* createWidget();

private:
    QString name;
    QString address;
    QString city;
    QDate birthdate;

};

ostream& operator<< (ostream& os, const CustClassic& c);
istream& operator>> (istream& is, CustClassic& c);
