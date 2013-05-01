
#include <QtGui>
#include <math.h>

#include "starrating.h"

const int PaintingScaleFactor = 20;

StarRating::StarRating(int starCount, int maxStarCount) {
    m_stars = starCount;
    m_maxStars = maxStarCount;

    m_starPolygon << QPointF(1.0, 0.5);
    for (int i = 1; i < 5; ++i)
        m_starPolygon << QPointF(0.5 + 0.5 * cos(0.8 * i * 3.14),
                               0.5 + 0.5 * sin(0.8 * i * 3.14));

    m_diamondPolygon << QPointF(0.4, 0.5) << QPointF(0.5, 0.4)
                   << QPointF(0.6, 0.5) << QPointF(0.5, 0.6)
                   << QPointF(0.4, 0.5);
}

QSize StarRating::sizeHint() const {
    return PaintingScaleFactor * QSize(m_maxStars, 1);
}

void StarRating::paint(QPainter *painter, const QRect &rect,
                       const QPalette &palette, EditMode mode) const {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    QBrush yellowBrush(QColor::fromCmyk(0,128,255,0));
    if (mode == Editable) {
        painter->setBrush(palette.highlight());
    } else {
        painter->setBrush(yellowBrush);

    }

    int yOffset = (rect.height() - PaintingScaleFactor) / 2;
    painter->translate(rect.x(), rect.y() + yOffset);
    painter->scale(PaintingScaleFactor, PaintingScaleFactor);

    for (int i = 0; i < m_maxStars; ++i) {
        if (i < m_stars) {
            painter->drawPolygon(m_starPolygon, Qt::WindingFill);
        } else if (mode == Editable) {
            painter->drawPolygon(m_diamondPolygon, Qt::WindingFill);
        }
        painter->translate(1.0, 0.0);
    }

    painter->restore();
}

