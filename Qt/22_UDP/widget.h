#ifndef WIDGET_H
#define WIDGET_H

#include <QUdpSocket> // UDP套接字
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

  void dealMsg(); // 槽函数，处理对方发来的数据

private slots:
  void on_sendButton_clicked();

  void on_closeButton_clicked();

private:
  Ui::Widget *ui;
  QUdpSocket *udpSocket; // UDP套接字
  QDateTime *dateTime;
};
#endif // WIDGET_H
