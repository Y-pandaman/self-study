#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QLabel {
  Q_OBJECT

public:
  MyWidget(QWidget *parent = nullptr);
  ~MyWidget();

protected:
  // 键盘按下事件
  void keyPressEvent(QKeyEvent *ev) override;
  // 定时器事件
  void timerEvent(QTimerEvent *ev) override;

  void mousePressEvent(QMouseEvent *ev) override;

  // 关闭事件
  void closeEvent(QCloseEvent *ev) override;

  bool event(QEvent *e) override;

  // 事件过滤器
  bool eventFilter(QObject *obj, QEvent *e) override;

private:
  Ui::MyWidget *ui;
  int timerId; // 定时器的标识id
  int timerId2;
};
#endif // MYWIDGET_H
