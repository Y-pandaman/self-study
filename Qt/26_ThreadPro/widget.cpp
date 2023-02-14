#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // 动态分配空间，不能指定父对象
  myThread = new MyThread;

  // 创建子线程
  thread = new QThread(this);

  // 把自定义的线程加入到子线程中
  myThread->moveToThread(thread);

  connect(myThread, &MyThread::mySignal, this, &Widget::dealSignal);
  qDebug() << "主线程号：" << QThread::currentThread();

  // 通过信号与槽调用线程处理函数
  connect(this, &Widget::startThread, myThread, &MyThread::myTimeout);

  // 点击窗口×按钮处理函数
  connect(this, &Widget::destroyed, this, &Widget::dealClose);

  // 线程处理函数内部不能操作图形界面

  // connect()第五个参数的作用，连接方式：默认，队列，直接
  // 多线程才有意义
  // 如果是多线程，默认使用队列
  // 如果是单线程，默认使用直接方式
  // 队列：槽函数所在的线程和接收者一样
  // 直接：槽函数所在的线程和发送者一样
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_startButton_clicked() {
  if (thread->isRunning()) {
    return;
  }
  // 启动线程，但没有启动线程处理函数
  thread->start();
  myThread->setFlag(false);

  // 不能直接调用线程处理函数
  // 直接调用，会导致线程处理函数和主线程在同一个线程
  //    myThread->myTimeout();  // ×

  // 只能通过信号-槽调用
  emit startThread();
}

void Widget::dealSignal() {
  static int num = 0;
  ui->lcdNumber->display(num++);
}

void Widget::dealClose() {
  on_stopButton_clicked();
  delete myThread; // 释放内存
}

void Widget::on_stopButton_clicked() {
  if (!thread->isRunning()) {
    return;
  }
  myThread->setFlag(true); // 更改标志位
  // 只写quit和wait，线程退出不了
  thread->quit();
  thread->wait();
}
