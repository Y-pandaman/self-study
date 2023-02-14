#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDateTime>

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ClientWidget) {
  ui->setupUi(this);

  // 获取当前时间
  QDateTime *datetime = new QDateTime(QDateTime::currentDateTime());

  tcpSocket = nullptr;
  tcpSocket = new QTcpSocket(this); // 分配空间

  connect(tcpSocket, &QTcpSocket::connected,
          [=]() { ui->textRead->setText("成功和服务器建立连接!"); });
  // 显示通信信息
  connect(tcpSocket, &QTcpSocket::readyRead, [=]() {
    QByteArray array = tcpSocket->readAll();

    QString time =
        datetime->toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    ui->textRead->append(time);
    ui->textRead->append(array);
  });
}

ClientWidget::~ClientWidget() {
    delete ui;
}

void ClientWidget::on_connectButton_clicked() {
  // 获取服务器ip和端口
  QString ip = ui->textIP->text();
  qint16 port = ui->textPort->text().toUInt();

  tcpSocket->connectToHost(ip, port);
}

void ClientWidget::on_sendButton_clicked() {
  QString str = ui->textWrite->toPlainText(); // 获取编辑框内容
  tcpSocket->write(str.toUtf8().data());      // 发送数据
  ui->textWrite->clear();                     // 清空编辑区
}

void ClientWidget::on_closeButton_clicked() {
  tcpSocket->disconnectFromHost(); // 主动断开连接
  tcpSocket->close();
}
