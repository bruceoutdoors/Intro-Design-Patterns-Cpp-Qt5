#ifndef FUNCTORS_H
#define FUNCTORS_H

#include <QString>
#include <QImage>
#include <functional>

const int imageSize = 100;
//start
/** A functor that only loads an image */
class Load : public std::unary_function<QString, QImage> {         /* Defines result_type. */
public:
    QImage operator() (const QString& imageFileName) const {
        return QImage(imageFileName);
    }
};

/** A functor that only scales an image. */
class Scale {
    public:
    typedef QImage result_type;                                    /* A trait required for functor objects. */
    QImage operator() (QImage image) const {
        for (int i=0; i<10; ++i) {
            QImage copy = image.copy();
            copy.scaled(100, 100, Qt::KeepAspectRatio);
        }
        if (image.width() < image.height()) {
            return image.scaledToHeight(imageSize,
                                        Qt::SmoothTransformation);
        }
        else {
            return image.scaledToWidth(imageSize, 
                                       Qt::SmoothTransformation);
        }
    }
};

/** A single functor that performs load and scale */
class LoadAndScale : public std::unary_function<QString, QImage> { /* Also defines result_type. */
public:
    Scale scale;
    QImage operator() (const QString& imageFileName) const {
        QImage image(imageFileName);
        return scale(image);
    }
};
//end
#endif // FUNCTORS_H
