#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  cheeseX = -1;
  cheeseY = -1;
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
  gridH = height() / 10; // 高度
  gridW = width() / 10;  // 宽度

  startX = gridW; // 起点x
  startY = gridH; // 起点y

  // 定义画笔，画布
  QPainter painter(this);
  painter.drawPixmap(rect(), QPixmap("../image/RegistFormBG.jpg")); // 背景
  QPen pen;
  pen.setWidth(4);
  painter.setPen(pen);

  // 画棋盘
  for (int i = 0; i <= 8; i++) {
    painter.drawLine(startX, startY + gridH * i, startX + 8 * gridW,
                     startY + gridH * i); // 九条横线
    painter.drawLine(startX + gridW * i, startY, startX + gridW * i,
                     startY + 8 * gridH); // 九条竖线
  }

  // 画棋子
  if (cheeseX != -1 && cheeseY != -1) {
    painter.drawPixmap(startX + cheeseX * gridW, startY + cheeseY * gridH,
                       gridW, gridH, QPixmap("../image/3.png"));
  }
}

void Widget::mousePressEvent(QMouseEvent *event) {
  // 获取鼠标坐标
  int pos_x = event->x();
  int pos_y = event->y();

  // 判断鼠标坐标是否在棋盘内
  if (pos_x >= startX && pos_x <= startX + 8 * gridW && pos_y >= startY &&
      pos_y <= startY + 8 * gridH) {
    cheeseX = (pos_x - startX) / gridW; // 获取棋盘格下标x
    cheeseY = (pos_y - startY) / gridH; // 获取棋盘格下标y
    qDebug() << cheeseX << cheeseY;

    update(); // 更新窗口
  }
}
