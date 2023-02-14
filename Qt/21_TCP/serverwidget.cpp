#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QDateTime>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ServerWidget) {
  ui->setupUi(this);

  QDateTime *datetime = new QDateTime(QDateTime::currentDateTime());

  tcpServer = nullptr;
  tcpSocket = nullptr;

  tcpServer = new QTcpServer(this); // 监听套接字，指定父对象，自动回收空间
  tcpServer->listen(QHostAddress::Any, 8080); // 监听
  setWindowTitle("服务器，端口号：8080");
  connect(tcpServer, &QTcpServer::newConnection, [=]() {
    // 取出建立好连接的套接字
    tcpSocket = tcpServer->nextPendingConnection();
    // 获取客户端的ip和端口号
    QString ip = tcpSocket->peerAddress().toString();
    qint16 port = tcpSocket->peerPort();
    QString temp = QString("[%1::%2]:成功连接").arg(ip).arg(port);
    ui->readText->setText(temp);

    connect(tcpSocket, &QTcpSocket::readyRead, [=]() {
      // 从通信套接字中取内容
      QByteArray array = tcpSocket->readAll();
      QString time =
          datetime->toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
      ui->readText->append(time);
      ui->readText->append(array);
    });
  });
}

ServerWidget::~ServerWidget() {
    delete ui;
}

void ServerWidget::on_sendButton_clicked() {
  if (tcpSocket == nullptr) {
    return;
  }
  // 获取编辑区内容
  QString str = ui->writeText->toPlainText();
  // 给对方发送数据 使用tcpSocket套接字
  tcpSocket->write(str.toUtf8().data());
  ui->writeText->clear();
}

void ServerWidget::on_closeButton_clicked() {
  if (tcpSocket == nullptr) {
    return;
  }
  tcpSocket->disconnectFromHost(); // 断开连接
  tcpSocket->close();
  tcpSocket = nullptr;
}
