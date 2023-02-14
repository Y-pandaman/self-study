#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent) {

}

void MyThread::run() {
  // 复杂的数据处理，耗时5秒，用sleep代替
  sleep(5);

  emit isDone();
}
