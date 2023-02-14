#ifndef WIDGET_H
#define WIDGET_H

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

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

private:
  Ui::Widget *ui;
  int gridW;   // 棋盘格宽度
  int gridH;   // 棋盘格高度
  int startX;  // 棋盘起点x
  int startY;  // 棋盘起点y
  int cheeseX; // 棋盘格下标x
  int cheeseY; // 棋盘格下标y
};
#endif // WIDGET_H
