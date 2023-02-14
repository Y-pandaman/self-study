#ifndef WIDGET_H
#define WIDGET_H

#include "mythread.h"
#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  void dealTimeout(); // 定时器槽函数
  void dealDone();    // 线程结束槽函数
  void stopThread();  // 停止线程槽函数

private slots:
  void on_pushButton_clicked();

private:
  Ui::Widget *ui;

  QTimer *timer;
  MyThread *thread; // 线程对象
};
#endif // WIDGET_H
