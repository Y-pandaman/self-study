#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ServerWidget) {
  ui->setupUi(this);

  tcpServer = new QTcpServer(this);           // 监听套接字
  tcpServer->listen(QHostAddress::Any, 8080); // 监听
  setWindowTitle("服务器端口为：8080");

  // 禁用按钮
  ui->selectButton->setEnabled(false);
  ui->sendButton->setEnabled(false);

  connect(tcpServer, &QTcpServer::newConnection, [=]() {
    // 取出建立好连接的套接字
    tcpSocket = tcpServer->nextPendingConnection();
    // 获取ip和port
    QString ip = tcpSocket->peerAddress().toString();
    quint16 port = tcpSocket->peerPort();

    QString str = QString("[%1:%2] 成功连接！").arg(ip).arg(port);
    ui->textEdit->setText(str);

    // 启用按钮
    ui->selectButton->setEnabled(true);

    connect(tcpSocket, &QTcpSocket::readyRead, [=]() {
      QByteArray buf = tcpSocket->readAll();
      if (QString(buf) == "done") {
        ui->textEdit->append("文件发送完毕");
        file.close(); // 关闭文件
        //              QMessageBox::information(this, "完成", "文件发送完毕");
        // 断开客户端
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
      }
      //          else{
      //              qDebug() << buf;
      //          }
    });
  });

  connect(&timer, &QTimer::timeout, [=]() {
    timer.stop(); // 停止定时器
    ui->textEdit->append("文件正在发送...");
    sendData();
  });
}

ServerWidget::~ServerWidget() {
    delete ui;
}

void ServerWidget::on_selectButton_clicked() {
  QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "../");
  if (!filePath.isEmpty()) {
    fileName.clear();
    fileSize = 0;

    // 获取文件信息
    QFileInfo info(filePath);
    fileName = info.fileName();
    fileSize = info.size();

    sendSize = 0; // 发送文件的大小

    // 只读方式打开
    file.setFileName(filePath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if (!isOk) {
      qDebug() << "只读方式打开文件错误!";
    }
    // 显示打开的文件路径
    ui->textEdit->append(filePath);

    // 启用按钮
    ui->selectButton->setEnabled(false);
    ui->sendButton->setEnabled(true);
  }
  else {
    qDebug() << "选择文件路径错误！";
  }
}

void ServerWidget::on_sendButton_clicked() {
  // 先发送文件头信息
  QString fileHead = QString("%1##%2").arg(fileName).arg(fileSize);
  //    qDebug() << fileHead;
  qint64 len = tcpSocket->write(fileHead.toUtf8());
  if (len > 0) {
    timer.start(200); // 启用定时器
  }
  else {
    qDebug() << "头信息发送失败";
    file.close();
    ui->selectButton->setEnabled(true);
    ui->sendButton->setEnabled(false);
  }
}

void ServerWidget::sendData() {
  qint64 len = 0;
  do {
    char buf[4096] = {0};              // 每次发送数据的大小
    len = file.read(buf, sizeof(buf)); // 往文件中读数据
    len = tcpSocket->write(buf, len);  // 发送数据，读多少，发多少
    sendSize += len;                   // 累加发送的数据
  } while (len > 0);

  //    if(sendSize == fileSize){
  ////        qDebug() << "sendSize:" << sendSize << "fileSize:" << fileSize;
  //        file.close(); // 关闭文件
  //        QMessageBox::information(this, "完成", "文件发送完毕");

  //        // 断开客户端
  //        tcpSocket->disconnectFromHost();
  //        tcpSocket->close();
  //    }
}
