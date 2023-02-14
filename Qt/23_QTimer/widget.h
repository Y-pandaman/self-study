#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer> // 定时器
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

private slots:
  void on_startButton_clicked();

  void on_stopButton_clicked();

private:
  Ui::Widget *ui;
  QTimer *timer;
};
#endif // WIDGET_H
