
#include <QtGui>

#include "stareditor.h"
#include "starrating.h"

StarEditor::StarEditor(QWidget* parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);
}

QSize StarEditor::sizeHint() const
{
    return m_starRating.sizeHint();
}

void StarEditor::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    m_starRating.paint(&painter, rect(), this->palette(),
                       StarRating::Editable);
}

void StarEditor::mouseMoveEvent(QMouseEvent* event)
{
    int star = starAtPosition(event->x());

    if (star != m_starRating.starCount() && star != -1) {
        m_starRating.setStarCount(star);
        update();
    }
}

void StarEditor::mouseReleaseEvent(QMouseEvent* /* event */)
{
    emit editingFinished();
}

int StarEditor::starAtPosition(int x)
{
    int star = (x / (m_starRating.sizeHint().width()
                     / m_starRating.maxStarCount())) + 1;
    if (star <= 0 || star > m_starRating.maxStarCount())
        return -1;

    return star;
}

