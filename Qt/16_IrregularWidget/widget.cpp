#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // 去窗口边框
  setWindowFlag(Qt::FramelessWindowHint);

  // 窗口背景设为透明
  setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, QPixmap("../image/3.png"));
}

void Widget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    close();
  }
  if (event->button() == Qt::LeftButton) {
    // 求坐标差值
    // 当前 点击坐标-窗口左上角坐标
    point = event->globalPos() - this->frameGeometry().topLeft();
  }
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    move(event->globalPos() - point);
  }
}
