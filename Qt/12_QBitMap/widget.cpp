#include "widget.h"
#include "ui_widget.h"
#include <QBitmap>
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() { delete ui; }

void Widget::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  // 图片背景透明
  painter.drawPixmap(0, 0, QPixmap("../image/3.png"));
  painter.drawPixmap(200, 0, QBitmap("../image/3.png"));

  // 图片背景白色
  // pixmap
  QPixmap pixmap;
  pixmap.load("../image/5.jpg");
  painter.drawPixmap(0, 200, pixmap);

  // bitmap
  QBitmap bitmap;
  bitmap.load("../image/5.jpg");
  painter.drawPixmap(500, 200, bitmap);
}
