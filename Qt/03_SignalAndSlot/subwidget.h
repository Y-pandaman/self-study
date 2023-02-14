#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QPushButton>
#include <QWidget>

class SubWidget : public QWidget {
  Q_OBJECT
public:
  explicit SubWidget(QWidget *parent = nullptr);

  void sendSlot();

  // 信号必须有signals关键字来声明
  // 信号没有返回值，但是可以有参数
  // 信号就是函数的声明，只需声明，无需定义
  // 使用：emit mySignal();
  // 信号可以重载
signals:
  void mySignal();
  void mySignal(int, QString);

public slots:

private:
  QPushButton button;
};

#endif // SUBWIDGET_H
