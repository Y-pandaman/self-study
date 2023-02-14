#include "mybutton.h"
#include <QDebug>
#include <QMouseEvent>

MyButton::MyButton(QWidget *parent) : QPushButton(parent) {}

void MyButton::mousePressEvent(QMouseEvent *ev) {
  if (ev->button() == Qt::LeftButton) {
    qDebug() << "Left key pressed"; // 事件接收后，就不会往下传递

    ev->ignore(); // 忽略，事件继续往下传递，但事件是传递给父组件MyWidget,而不是父类（基类）QWidget
  }
  else {
    QPushButton::mousePressEvent(ev); // 不做处理，事件忽略，事件继续往下传递
  }
}
