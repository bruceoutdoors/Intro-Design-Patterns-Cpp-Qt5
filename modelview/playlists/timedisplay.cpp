#include "timedisplay.h"

TimeDisplay::TimeDisplay(QWidget* parent)
: QTimeEdit(parent) {
    setObjectName("TimeDisplay");
	setReadOnly(true);
	setDisplayFormat("mm:ss");
	setButtonSymbols(NoButtons);
}


