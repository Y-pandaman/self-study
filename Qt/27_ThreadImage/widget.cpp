#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // 自定义类对象，分配空间，不可以指定父对象
  myThread = new MyThread;

  //创建子线程
  thread = new QThread(this);

  // 把自定义模块添加到子线程
  myThread->moveToThread(thread);

  // 启动子线程，但没有启动线程处理函数
  thread->start();

  // 线程处理函数必须通过信号与槽调用
  connect(ui->pushButton, &QPushButton::pressed, myThread,
          &MyThread::drawImage);
  connect(myThread, &MyThread::updateImage, this, &Widget::getImage);

  connect(this, &Widget::destroyed, this, &Widget::dealClose);
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *ev) {
  QPainter painter(this); // 创建画家，指定绘图设备为窗口
  painter.drawImage(0, 0, image);
}

void Widget::getImage(QImage temp) {
  image = temp;
  update(); // 间接调用paintEvent()
}

void Widget::dealClose() {
  thread->quit();
  thread->wait();
  delete myThread;
}
