#ifndef TIMEDISPLAY_H
#define TIMEDISPLAY_H

#include <QTimeEdit>

class TimeDisplay : public QTimeEdit {
	Q_OBJECT
public:
	TimeDisplay(QWidget* parent=0);
};

#endif        //  #ifndef TIMEDISPLAY_H

