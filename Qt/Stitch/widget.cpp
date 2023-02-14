#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    ui->pushButton_stitch->setEnabled(false);
    ui->pushButton_clear->setEnabled(false);
    mImg_w = ui->label->width();
    mImg_h = ui->label->height();
}

Widget::~Widget() { delete ui; }

//图像转换函数（opencv Mat转换为QImage)
QImage Widget::Mat2QImage(cv::Mat const &src) {
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

    const float scale = 255.0;

    if (src.depth() == CV_8U) {
        if (src.channels() == 1) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    int level = src.at<quint8>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        } else if (src.channels() == 3) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    } else if (src.depth() == CV_32F) {
        if (src.channels() == 1) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    int level = scale * src.at<float>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        } else if (src.channels() == 3) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    }

    return dest;
}
//图像转换函数（QImage转换为opencv Mat)
cv::Mat Widget::QImage2Mat(QImage &image) {
    cv::Mat mat;
    switch (image.format()) {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4,
                      (void *)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3,
                      (void *)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1,
                      (void *)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    QString img_name = item->text();
    QString img_path = "/home/bdca/workspace/stitch_ws/src/data/" + img_name;
    img = cv::imread(img_path.toStdString());

    if (ui->checkBox_divide->isChecked()) {
        cv::Rect rect(0, 0, img.cols / 2, img.rows);
        imgs.push_back(img(rect).clone());
        rect.x = img.cols / 3;
        imgs.push_back(img(rect).clone());
        rect.x = img.cols / 2;
        imgs.push_back(img(rect).clone());
    } else {
        imgs.push_back(img);
    }
}

void Widget::on_pushButton_stitch_clicked() {
    if (ui->checkBox_use_GPU->isChecked()) {
        try_use_gpu = true;
    } else {
        try_use_gpu = false;
    }

    if (ui->comboBox_mode->currentIndex() == 0) {
        mode = cv::Stitcher::Mode::PANORAMA;
    } else {
        mode = cv::Stitcher::Mode::SCANS;
    }

    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode, try_use_gpu);
    struct timeval time;
    gettimeofday(&time, NULL);
    t1 = time.tv_sec * 1000.0 + time.tv_usec / 1000.0;

    cv::Stitcher::Status status = stitcher->stitch(imgs, pano);

    gettimeofday(&time, NULL);
    t2 = time.tv_sec * 1000.0 + time.tv_usec / 1000.0;
    ui->lineEdit->setText(QString::number(t2 - t1));

    QImage stitch_image = Mat2QImage(pano);
    QSize PixSize = ui->label->size();
    stitch_image.scaled(PixSize, Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(stitch_image));
    if (stitch_image.width() > stitch_image.height()) {
        ui->label->resize(mImg_w,
                          stitch_image.height() * mImg_w /
                              stitch_image.width()); // 等比例缩放图片
    } else {
        ui->label->resize(stitch_image.width() * mImg_h /
                              stitch_image.height(),
                          mImg_h);
    }
}

void Widget::on_pushButton_clear_clicked() {
    imgs.clear();
    ui->label->clear();
    ui->lineEdit->clear();
}

void Widget::on_pushButton_open_clicked() {
    ui->listWidget->clear();

    // 方法 1
    //    QString file = QFileDialog::getOpenFileName(this, "open file", "../../",
    //    "IMG(*.png, *.jpg)"); QFileInfo file_info = QFileInfo(file); QString
    //    root = file_info.absolutePath();
    // 方法 2
    //    QString root = "/home/bdca/workspace/stitch_ws/src/data";
    //    //文件存在的目录

    // 方法 3
    QString root =
        QFileDialog::getExistingDirectory(this, "open folder", "../../");

    QDir rootDir(root);
    QString name1 = "*.jpg"; //选择要筛选的文件类型
    QString name2 = "*.png";
    QStringList filters; //筛选器
    filters << name1 << name2;
    QFileInfoList list = rootDir.entryInfoList(filters);
    if(list.count() > 0){
        ui->pushButton_stitch->setEnabled(true);
        ui->pushButton_clear->setEnabled(true);
    }
    else{
        ui->pushButton_stitch->setEnabled(false);
        ui->pushButton_clear->setEnabled(false);
    }

    for (unsigned int i = 0; i < list.count(); i++) {
        QFileInfo tmpFileInfo = list.at(i);
        if (tmpFileInfo.isDir()) {
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(fileName);
            ui->listWidget->addItem(tmp);
        } else if (tmpFileInfo.isFile()) {
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp = new QListWidgetItem(fileName);
            ui->listWidget->addItem(tmp);
        }
    }
}
