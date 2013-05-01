#include <QPainter>
#include "lifewidget.h"

//start id="paintevent"
void LifeWidget::paintEvent(QPaintEvent *evt) {
    QPainter painter(this);         /* First line of most paintEvents */
    if (!m_image.isNull())
        painter.drawImage(QPoint(0,0), m_image);
}
//end


//start id="setImage"
void LifeWidget::setImage(QImage image) {
    m_size = image.size();
    m_image = image.scaled(size());
    update();        /* asynchronous - return immediately */
}
//end

LifeWidget::LifeWidget(QWidget *parent) :  QWidget(parent) {
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

QSize LifeWidget::sizeHint() const {
    return m_size;
}


LifeWidget::~LifeWidget() { }
