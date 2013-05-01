#ifndef PREFERENCECOMBO_H
#define PREFERENCECOMBO_H

#include "metadataexport.h"

#include <QComboBox>
class METADATAEXPORT PreferenceCombo : public QComboBox {
    Q_OBJECT
public:
    PreferenceCombo(QWidget* parent=0);
};

#endif        //  #ifndef PREFERENCECOMBO_H

