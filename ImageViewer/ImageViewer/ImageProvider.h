#pragma once

#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QObject>
#include <QImage>
#include <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider
{
    Q_OBJECT
public:
    ImageProvider(QObject* parent = nullptr);

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

public slots:
    void updateImage(const QImage& image);

signals:
    void imageChanged();

private:
    QImage image;
};

#endif