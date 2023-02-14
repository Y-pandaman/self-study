#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QTcpServer> // 监听套接字
#include <QTcpSocket> //通信套接字
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ServerWidget;
}
QT_END_NAMESPACE

class ServerWidget : public QWidget {
  Q_OBJECT

public:
  ServerWidget(QWidget *parent = nullptr);
  ~ServerWidget();

private slots:
  void on_sendButton_clicked();

  void on_closeButton_clicked();

private:
  Ui::ServerWidget *ui;

  QTcpServer *tcpServer; // 监听套接字
  QTcpSocket *tcpSocket; //通信套接字
};
#endif // SERVERWIDGET_H
