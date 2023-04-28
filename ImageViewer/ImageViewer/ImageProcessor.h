#pragma once
#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H


#include <QObject>
#include <QImage>
#include <QString>
#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

class ImageProcessor:public QObject
{
    Q_OBJECT
    public:
        ImageProcessor();
        ~ImageProcessor();        

        QImage mat_to_qimage_ref(cv::Mat&, QImage::Format);

    public slots:
        void loadInitial(const QString filepath);
        void AnnotTextAt(float x, float y, const QString annotTxt);
        void AnnotTextWithBoxSelect(float x, float y, float width, float height, const QString annotTxt);

    private:
        cv::Mat imaged;

    signals:
    void newImage(QImage&);
};
#endif
