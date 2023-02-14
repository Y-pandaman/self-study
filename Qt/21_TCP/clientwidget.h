#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H
#include <QTcpSocket> // 通信套接字

#include <QWidget>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget {
  Q_OBJECT

public:
  explicit ClientWidget(QWidget *parent = nullptr);
  ~ClientWidget();

private slots:
  void on_connectButton_clicked();

  void on_sendButton_clicked();

  void on_closeButton_clicked();

private:
  Ui::ClientWidget *ui;
  QTcpSocket *tcpSocket;
};

#endif // CLIENTWIDGET_H
