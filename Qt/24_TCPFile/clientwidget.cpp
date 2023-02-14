#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ClientWidget) {
  ui->setupUi(this);

  tcpSocket = new QTcpSocket(this);
  isStart = true;
  ui->progressBar->setValue(0);

  connect(tcpSocket, &QTcpSocket::readyRead, [=]() {
    // 读数据
    QByteArray buf = tcpSocket->readAll();
    if (isStart) { // 接收头
      isStart = false;
      // 解析头信息
      // 拆包，以##为分隔，第0段到第0段
      fileName = QString(buf).section("##", 0, 0);
      fileSize = QString(buf).section("##", 1, 1).toInt();
      recvSize = 0; // 清0 很重要

      ui->progressBar->setMinimum(0);
      ui->progressBar->setMaximum(fileSize);

      // 打开文件
      file.setFileName(fileName);
      bool isOk = file.open(QIODevice::WriteOnly);
      if (!isOk) {
        qDebug() << "打开出错";
      }
    } else {
      qint64 len = file.write(buf);
      recvSize += len;
      //      //测试黏包
      //      QString str = QString::number(recvSize);
      //      tcpSocket->write(str.toUtf8().data());
      ui->progressBar->setValue(recvSize);

      if (recvSize == fileSize) {
        qDebug() << "传输完成";
        tcpSocket->write("done");
        QMessageBox::information(this, "完成", "文件接收完成");
        file.close();

        // 断开连接
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
      }
    }
  });
}

ClientWidget::~ClientWidget() {
    delete ui;
}

void ClientWidget::on_connectButton_clicked() {
  // 获取ip和端口
  QString ip = ui->textIP->text();
  quint64 port = ui->textPort->text().toUInt();

  tcpSocket->connectToHost(QHostAddress(ip), port); // 连接
}
