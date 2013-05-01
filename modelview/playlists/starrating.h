
#ifndef STARRATING_H
#define STARRATING_H

#include <QMetaType>
#include <QPointF>
#include <QVector>
#include <QPolygonF>
#include <QPainter>

/* Based on the Qt examples */
class StarRating {
public:
    enum EditMode { Editable, ReadOnly };

    /** Defines a conversion ctor from int to StarRating(int, 5) */
    StarRating(int starCount = 1, int maxStarCount = 5);

    void paint(QPainter* painter, const QRect& rect,
               const QPalette& palette, EditMode mode) const;
    QSize sizeHint() const;
    int starCount() const { return m_stars; }
    int maxStarCount() const { return m_maxStars; }
    void setStarCount(int starCount) { m_stars = starCount; }
    void setMaxStarCount(int maxStarCount) { m_maxStars = maxStarCount; }

private:
    QPolygonF m_starPolygon;
    QPolygonF m_diamondPolygon;
    int m_stars;
    int m_maxStars;
};

inline bool operator<(const StarRating& l, const StarRating& r) {
    return l.starCount() < r.starCount();
}

// 
/** Add to QVariant type system
    Be sure to qRegisterMetaType<StarRating>("StarRating") in your program 
    before using it for the first time. */
Q_DECLARE_METATYPE(StarRating)

#endif

