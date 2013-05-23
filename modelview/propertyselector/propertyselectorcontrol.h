#ifndef PROPERTYSELECTORCONTROL_H
#define PROPERTYSELECTORCONTROL_H

#include "propertyselectormodel.h"
#include "propertyselectorview.h"

#include <QObject>
#include <QMainWindow>

class PropertySelectorControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit PropertySelectorControl(DataObject* sourceptr);
    QString getSelectedPropertyNames() const;

public slots:
    void outputSelects(bool);
    void showWindow(bool);

signals:
    void readyShow();

private:
    PropertySelectorModel* m_Chdm;
    PropertySelectorView* m_Chdv;
};

#endif // PROPERTYSELECTORCONTROL_H
