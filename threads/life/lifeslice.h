#ifndef LIFESLICE_H
#define LIFESLICE_H

#include <QRect>
#include <QImage>


/** A piece of work - a "slice of life" of Conway's game of life.
*/
//start
struct LifeSlice {
    LifeSlice() {};
    LifeSlice(QRect r, QImage i) : rect(r), image(i) {}

    /** Rectangle that this slice belongs in */
    QRect rect;
    /** image data */
    QImage image;
};
//end

#endif // LIFESLICE_H
