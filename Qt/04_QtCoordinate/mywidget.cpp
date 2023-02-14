#include "mywidget.h"
#include "mybutton.h"
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
  // 对于父窗口（主窗口），坐标系统相对于屏幕
  // 原点：屏幕左上角
  // x:从左向右
  // y:从上向下
  move(100, 100);

  // 子窗口，坐标系统相对于父窗口
  // 原点：窗口空白区域左上角，不包括边框
  // x:从左向右
  // y:从上向下
  QPushButton *button1 = new QPushButton(this);
  button1->setText("按钮1");
  button1->move(50, 50);                  // 位置
  button1->resize(100, 100);              // 大小
  button1->setGeometry(50, 50, 100, 100); // 同时设置位置和大小

  QPushButton *button2 = new QPushButton(button1); // 坐标系统相对于button1
  button2->move(10, 10);
  button2->setText("按钮2");

  // 指定父对象后，子对象如果是动态分配空间的new,不需要手动释放delete，系统会自动释放
  // 直接或间接继承与QObject
  MyButton *button3 = new MyButton(this);
  button3->setText("按钮3");
}

MyWidget::~MyWidget() {}
