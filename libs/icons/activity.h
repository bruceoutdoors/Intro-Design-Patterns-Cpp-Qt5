#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QPushButton>
#include <QIcon>
#include <QMovie>
#include "icons_export.h"
/** @return a QMovie singleton with a spinning activity icon.
    Shared by ActivityButton and ActivityItem. */
ICONS_EXPORT QMovie* getMovie();

/** @return a QIcon for getMovie()'s current frame */
ICONS_EXPORT QIcon getCurrentIcon();

/** A QPushButton which will show a spinny icon if you setActive(true) */
class ICONS_EXPORT  ActivityButton : public QPushButton {
    Q_OBJECT
public:
    ActivityButton(QString text, QWidget* parent =0);
    /** @return true if the icon is spinning */
    bool isActive() const;  
public slots:
    /** @param isActive if true, start spinning the spinner icon */
    void setActive(bool isActive);
protected slots:
    void updateIcon();
private:
    bool m_isActive;
};

#endif        //  #ifndef ACTIVITY_H
