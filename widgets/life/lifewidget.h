#ifndef LIFEWIDGET_H
#define LIFEWIDGET_H

#include <QWidget>
#include <QImage>
//start
class LifeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LifeWidget(QWidget* parent = 0);
    ~LifeWidget();
    QSize sizeHint() const;
    void paintEvent(QPaintEvent* evt);      /* Custom paint event */
public slots:
    void setImage(const QImage& image);
private:
    QImage m_image;
    QSize m_size;
};
//end
#endif // LIFEWIDGET_H
