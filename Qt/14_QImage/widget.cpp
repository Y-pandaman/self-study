#include "widget.h"
#include "ui_widget.h"
#include <QImage>
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // 创建image绘图设备，QImage::Format_ARGB32背景是透明的
  QImage image(400, 300, QImage::Format_ARGB32);

  QPainter painter; // 创建画布
  painter.begin(&image);  // 开始绘图

  painter.drawImage(0, 0, QImage("../image/3.png")); // 绘图

  for(int i = 0; i < 50 ; i ++){
      for(int j = 0; j < 50; j ++){
          image.setPixel(QPoint(i, j), qRgb(255, 0, 0));  // 给像素赋值
          image.pixel(QPoint(50, 50));  // 获取像素值
      }
  }

  painter.end(); // 结束绘图

  image.save("../image/image.png"); // 保存
}

Widget::~Widget() {
    delete ui;
}
