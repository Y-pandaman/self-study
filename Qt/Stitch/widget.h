#ifndef WIDGET_H
#define WIDGET_H

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/stitching.hpp"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QLabel>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPixmap>
#include <QProcess>
#include <QThread>
#include <QWidget>
#include <QtGui>
#include <string>
#include <sys/time.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

  public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

  private slots:

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_stitch_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_open_clicked();

private:
    QImage Mat2QImage(cv::Mat const &src);
    cv::Mat QImage2Mat(QImage &image);
    Ui::Widget *ui;
    cv::Mat pano;
    std::vector<cv::Mat> imgs;
    bool try_use_gpu = false;
    bool divide_images = false;
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
    cv::Mat img;
    double t1 = 0;
    double t2 = 0;
    int mImg_w = 0;
    int mImg_h = 0;
};
#endif // WIDGET_H
