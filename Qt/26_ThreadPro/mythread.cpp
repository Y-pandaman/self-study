#include "mythread.h"
#include <QDebug>
#include <QThread>

MyThread::MyThread(QObject *parent) : QObject(parent) {
    isStop = false;
}

void MyThread::myTimeout() {
  while (!isStop) {
    QThread::sleep(1);
    emit mySignal();
    qDebug() << "子线程号：" << QThread::currentThread();

    if (isStop) {
      break;
    }
  }
}

void MyThread::setFlag(bool flag) {
    isStop = flag;
}
