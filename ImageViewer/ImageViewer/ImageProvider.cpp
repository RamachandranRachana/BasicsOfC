#include "ImageProvider.h"

ImageProvider::ImageProvider(QObject* parent) : QQuickImageProvider(QQuickImageProvider::Image)
{
    image = QImage(200, 200, QImage::Format_BGR888);
    image.fill(QColor("LightGray"));
}


QImage ImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    Q_UNUSED(id);

    if (size) {
        *size = image.size();
    }

    if (requestedSize.width() > 0 && requestedSize.height() > 0) {
        image = image.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);
    }
    return image;
}

void ImageProvider::updateImage(const QImage& imaged)
{

    if (!imaged.isNull())//&& this->image != image) 
    {
        this->image = imaged;
        emit imageChanged();
    }
}
