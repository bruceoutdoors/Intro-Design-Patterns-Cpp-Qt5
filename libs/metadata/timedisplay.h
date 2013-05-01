#ifndef TIMEDISPLAY_H
#define TIMEDISPLAY_H

#include "metadataexport.h"
#include <QTimeEdit>

/** A read-only QTimeEdit for displaying track duration */
class METADATAEXPORT TimeDisplay : public QTimeEdit {
	Q_OBJECT
public:
        TimeDisplay(QWidget* parent=0);
};

#endif        //  #ifndef TIMEDISPLAY_H

