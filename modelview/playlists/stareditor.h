#ifndef STAREDITOR_H
#define STAREDITOR_H

#include <QWidget>

#include "starrating.h"

/** Based on the Qt examples */

class StarEditor : public QWidget
{
    Q_OBJECT

public:
    StarEditor(QWidget* parent = 0);

    QSize sizeHint() const;

    void setStarRating(const StarRating& starRating) {
        m_starRating = starRating;
    }
    StarRating starRating() { return m_starRating; }

signals:
    void editingFinished();

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    int starAtPosition(int x);

    StarRating m_starRating;
};

#endif

