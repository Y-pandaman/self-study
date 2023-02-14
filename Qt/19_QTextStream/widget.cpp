#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  dataWrite();
  dataRead();
}

Widget::~Widget() {
    delete ui;
}

void Widget::dataWrite() {
  QFile file;                                  // 创建文件对象
  file.setFileName("../txt/textstream.txt");   // 设置文件名
  bool isOk = file.open(QIODevice::WriteOnly); // 只读方式打开文件
  if (isOk) {
    QTextStream textStream(&file); // 创建文本流 ,和file关联
    textStream.setCodec("UTF-8");  // 指定编码格式
    textStream << QString("主要看气质")  << 250; // 写数据,不自动间隔
    textStream << QString("主要看气质") << " " << 250; // 写数据
    file.close();                               // 关闭文件
  }
}

void Widget::dataRead() {
  QFile file;                                 // 创建文件对象
  file.setFileName("../txt/textstream.txt");  // 设置文件名
  bool isOk = file.open(QIODevice::ReadOnly); // 只读方式打开文件
  if (isOk) {
    QTextStream textStream(&file); // 创建文本流 ,和file关联
    textStream.setCodec("UTF-8");  // 指定编码格式
    QString str;
    int num;
    textStream >> str >> num;
    cout << str << num;
    file.close(); // 关闭文件
  }
}

void Widget::on_writeButton_clicked() {
  QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "../txt/");
  if (!filePath.isEmpty()) {
    QFile file;
    file.setFileName(filePath);

    bool isOk = file.open(QIODevice::ReadOnly);
    if (isOk) {
      QTextStream textStream(&file);
      textStream.setCodec("UTF-8"); // 指定编码
      QString str = textStream.readAll();
      ui->textEdit->setText(str);
    }
  }
}
