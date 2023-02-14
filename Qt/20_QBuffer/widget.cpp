#include "widget.h"
#include "ui_widget.h"
#include <QBuffer> // 内存文件
#include <QDataStream>
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // 方式1
  QByteArray array;
  QBuffer memFile(&array); // 创建内存文件

//  QBuffer memFile; // 方式2
  memFile.open(QIODevice::WriteOnly);
  memFile.write("1111111");
  memFile.write("22222222");
  memFile.close();
  qDebug() << memFile.buffer();
  qDebug() << "array:" << array;

  // 用QDataStream方式读写
  QBuffer memFile1;
  memFile1.open(QIODevice::WriteOnly);
  QDataStream stream(&memFile1);
  stream << QString("测试") << 250;
  memFile1.close();
  qDebug() << memFile1.buffer();

  memFile1.open(QIODevice::ReadOnly);
  QDataStream out;
  out.setDevice(&memFile1);
  QString str;
  int num;
  out >> str >> num;
  memFile1.close();
  qDebug() << str.toUtf8().data() << num;
}

Widget::~Widget() {
    delete ui;
}
