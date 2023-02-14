#ifndef WIDGET_H
#define WIDGET_H

#include "mythread.h"
#include <QImage>
#include <QThread>
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

  void paintEvent(QPaintEvent *ev) override; // 重写绘图事件

  void getImage(QImage temp);

  void dealClose(); // 窗口关闭槽函数

private:
  Ui::Widget *ui;
  QImage image;
  MyThread *myThread; // 自定义线程
  QThread *thread;
};
#endif // WIDGET_H
