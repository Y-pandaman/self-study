#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPicture>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  QPicture picture;
  QPainter painter;
  painter.begin(&picture);
  painter.drawPixmap(0, 0, 80, 90, QPixmap("../image/3.png"));
  painter.drawLine(50, 50, 150, 50);
  painter.end();
//  picture.save("../image/picture.bin");
  picture.save("../image/picture.png");  // 保存的是二进制文件
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *ev) {
#if 0
  QPicture pic;
//  pic.load("../image/picture.bin");
  pic.load("../image/picture.png");
  QPainter painter(this);
  painter.drawPicture(0, 0, pic);
#endif

  QPainter painter(this);

  // QPixmap  -> QImage
  QPixmap pixmap;
  pixmap.load("../image/3.png");
  QImage tempImage = pixmap.toImage();
  painter.drawImage(0, 0, tempImage);

  // QImage -> QPixmap
  QImage image;
  image.load("../image/3.png");
  QPixmap tempPixmap = QPixmap::fromImage(image);
  painter.drawPixmap(200,0,tempPixmap);

}
