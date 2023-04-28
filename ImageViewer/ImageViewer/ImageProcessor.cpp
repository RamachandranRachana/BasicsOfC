#include "ImageProcessor.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QPainter>
ImageProcessor::ImageProcessor()
{
    
}

ImageProcessor::~ImageProcessor()
{

}

void ImageProcessor::loadInitial(const QString filepath) {
    std::string path = filepath.toStdString();
    imaged = cv::imread(path);
    QImage img = mat_to_qimage_ref(imaged, QImage::Format_BGR888);
    cv::imwrite("test1.jpg", imaged);
    emit newImage(img);
}

void ImageProcessor::AnnotTextAt(float x, float y, const QString annotTxt) {
    QImage img = mat_to_qimage_ref(imaged, QImage::Format_BGR888);
    QPainter p(&img);
    p.setPen(QPen(Qt::red));
    p.setFont(QFont("Times", 100, QFont::Bold));
    QPointF point(x, y);
    p.drawText(point, "Text");
    emit newImage(img);
}

void ImageProcessor::AnnotTextWithBoxSelect(float x, float y,float width,float height, const QString annotTxt) {
    QImage img = mat_to_qimage_ref(imaged, QImage::Format_BGR888);
    QPainter p(&img);
    QPen textPen(Qt::red);
    QPen rectPen(Qt::green);
    rectPen.setWidth(20);

    p.setPen(textPen);
    p.setFont(QFont("Times", 100, QFont::Bold));
    QPointF point(x, y);
    p.drawText(point, "Text");

    p.setPen(rectPen);
    p.drawRect(x, y, width, height);
    emit newImage(img);
}

QImage ImageProcessor::mat_to_qimage_ref(cv::Mat& mat, QImage::Format format)
{
    return QImage(mat.data, mat.cols, mat.rows, mat.step, format);
}