#ifndef METADATAWIDGET_H
#define METADATAWIDGET_H


#include <QList>
#include <QWidget>
#include "metadataobject.h"

class QButtonGroup;
class QDataWidgetMapper;

#include "ui_metadatawidget.h"
#include "metadataexport.h"

/** A widget that can display and edit values in a MetaDataObject.
    TODO: Make it work with the QDataWidgetMapper?
*/
class METADATAEXPORT MetaDataWidget : public QWidget, private Ui::MetaDataWidget {
    Q_OBJECT
public:
    MetaDataWidget(QWidget* parent=0);

    /** Loads data from obj into the widget */

    void clear();
    MetaDataObject* model() const;

public slots:
    void processButton ( QAbstractButton * button );
    void display(const MetaDataValue& mdv);
    void submit();
    void revert();

private:
    MetaDataObject* m_model;
    QDataWidgetMapper* m_Mapper;

};

#endif        //  #ifndef METADATAWIDGET_H
