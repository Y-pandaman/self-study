#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QThread>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  timer = new QTimer(this);
  thread = new MyThread(this);

  // 定时器启动，自动触发timeout()
  connect(timer, &QTimer::timeout, this, &Widget::dealTimeout);

  connect(thread, &MyThread::isDone, this, &Widget::dealDone);

  // 点击窗口右上角×时，触发destroyed（）
  connect(this, &Widget::destroyed, this, &Widget::stopThread);
}

Widget::~Widget() {
    delete ui;
}

void Widget::dealTimeout() {
  static int num = 0;
  ui->lcdNumber->display(num++);
}

void Widget::dealDone() {
  qDebug() << "it is over";
  timer->stop(); // 关闭定时器
}

void Widget::stopThread() {
  thread->quit(); // 停止线程
  thread->wait(); // 等待线程处理完工作
}

void Widget::on_pushButton_clicked() {
  if (!timer->isActive()) {
    timer->start(100);
  }

  // 启动线程
  thread->start();
}
