#include "mylabel.h"

#include <QDebug>
#include <QMouseEvent>

MyLabel::MyLabel(QWidget* parent) : QLabel(parent) {
  this->setMouseTracking(true);  // 设置默认追踪鼠标
}

void MyLabel::mousePressEvent(QMouseEvent* ev) {
  int i = ev->x();
  int j = ev->y();

  // sprintf
  // QString str = QString("abc %1 ^-^ %2").arg(123).arg("milk")
  // str = abc 123 ^-^ milk

  if (ev->button() == Qt::LeftButton) {
    qDebug() << "Left";
  }
  else if (ev->button() == Qt::RightButton) {
    qDebug() << "Right";
  }
  else if (ev->button() == Qt::MidButton) {
    qDebug() << "Middle";
  }

  QString str =
      QString("<center><h1>鼠标点击坐标:(%1, %2)</h1></center>").arg(i).arg(j);
  this->setText(str);
}

void MyLabel::mouseReleaseEvent(QMouseEvent* ev) {
  QString str = QString("<center><h1>鼠标释放坐标:(%1, %2)</h1></center>")
                    .arg(ev->x())
                    .arg(ev->y());
  this->setText(str);
}

void MyLabel::mouseMoveEvent(QMouseEvent* ev) {
  QString str = QString("<center><h1>鼠标移动坐标:(%1, %2)</h1></center>")
                    .arg(ev->x())
                    .arg(ev->y());
  this->setText(str);
}

void MyLabel::enterEvent(QEvent* e) {
  QString str = QString("<center><h1>鼠标进入</h1></center>");
  this->setText(str);
}

void MyLabel::leaveEvent(QEvent* e) {
  QString str = QString("<center><h1>鼠标离开</h1></center>");
  this->setText(str);
}
