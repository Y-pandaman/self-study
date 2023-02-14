#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
#include <QHostAddress>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  dateTime = new QDateTime(QDateTime::currentDateTime());

  udpSocket = new QUdpSocket(this); // 分配空间，指定父对象，自动回收空间
  udpSocket->bind(8080);            // 绑定端口号

  // 加入组播，组播地址是D类地址
  //  udpSocket->bind(QHostAddress::AnyIPv4, 8080);
  //  udpSocket->joinMulticastGroup(QHostAddress("224.0.0.10"));
  //  udpSocket->leaveMulticastGroup(QHostAddress("224.0.0.10")); // 离开组播

  setWindowTitle("UDP服务器端口：8080"); // 窗口标题

  // 当对方发送数据过来，自动触发readyRead()
  connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::dealMsg);
}

Widget::~Widget() {
    delete ui;
}

void Widget::dealMsg() {
  // 读取对方发送的内容
  char buf[1024] = {0};
  QHostAddress ip;
  quint16 port;
  qint64 len = udpSocket->readDatagram(buf, sizeof(buf), &ip, &port);
  if (len > 0) {
    // 格式化
    QString str = QString("[%1:%2] %3").arg(ip.toString()).arg(port).arg(buf);
    QString time = dateTime->toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->textRead->append(time);
    ui->textRead->append(str); // 编辑区显示内容
  }
}

void Widget::on_sendButton_clicked() {
  // 获取对方ip和port
  QString ip = ui->textIP->text();
  qint16 port = ui->textPort->text().toInt();

  QString str = ui->textWrite->toPlainText();
  udpSocket->writeDatagram(str.toUtf8().data(), QHostAddress(ip), port);
  ui->textWrite->clear();
}

void Widget::on_closeButton_clicked() {
  udpSocket->close();
  close();
}
