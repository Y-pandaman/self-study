#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QDebug>
#include <QFile>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  writeData();
  readData();
}

Widget::~Widget() {
    delete ui;
}

void Widget::writeData() {
  QFile file("../txt/stream.txt");             // 创建文件对象
  bool isOk = file.open(QIODevice::WriteOnly); // 只读方式打开
  if (isOk) {
    // 创建数据流，和file文件关联
    // 往数据流中输入数据，相当于往文件里写数据
    QDataStream dataStream(&file);

    dataStream << QString("主要看气质") << 250; // 保存成二进制格式
    file.close();
  }
}

void Widget::readData() {
  QFile file("../txt/stream.txt");            // 创建文件对象
  bool isOk = file.open(QIODevice::ReadOnly); // 只读方式打开
  if (isOk) {
    // 创建数据流，和file文件关联
    // 往数据流中输入数据，相当于往文件里写数据
    QDataStream dataStream(&file);

    // 按写文件的顺序读文件
    QString str;
    int num;
    dataStream >> str >> num;
    //    qDebug() << str.toUtf8().data() << num;
    cout << str.toUtf8().data() << num;
    file.close();
  }
}
