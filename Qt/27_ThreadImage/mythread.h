#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QImage>
#include <QObject>

class MyThread : public QObject {
  Q_OBJECT
public:
  explicit MyThread(QObject *parent = nullptr);

  void drawImage(); // 线程处理函数

signals:
  void updateImage(QImage image); // 信号
};

#endif // MYTHREAD_H
