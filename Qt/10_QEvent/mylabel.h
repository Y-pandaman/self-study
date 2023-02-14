#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel {
  Q_OBJECT
public:
  explicit MyLabel(QWidget *parent = nullptr);

protected:
  // 鼠标点击事件
  void
  mousePressEvent(QMouseEvent *ev) override; // override让编译器检查是否有重写
  // 鼠标释放事件
  void mouseReleaseEvent(QMouseEvent *ev) override;
  // 鼠标移动事件
  void mouseMoveEvent(QMouseEvent *ev) override;
  //进入窗口区域
  void enterEvent(QEvent *e) override;
  // 离开窗口区域
  void leaveEvent(QEvent *e) override;

signals:
};

#endif // MYLABEL_H
