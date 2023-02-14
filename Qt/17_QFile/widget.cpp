#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_readButton_clicked() {
  QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "../",
                                                  "TXT(*.txt)"); // 获取文件路径
  if (filePath.isEmpty() == false) {
    QFile file(filePath);                       // 创建文件对象
    bool isOk = file.open(QIODevice::ReadOnly); // 打开文件，只读模式
    if (isOk) {
#if 0
       // 第一种方式
      QByteArray array = file.readAll(); // 读文件，默认只识别utf-8，一次性读取
//      ui->textEdit->setText(QString(array));  // 显示到文本框
      ui->textEdit->setText(array);
#endif

      // 第二种方式
      QByteArray array;
      while (file.atEnd() == false) {
        array += file.readLine(); // 按行读
      }
      ui->textEdit->setText(array); // 显示到文本框
    }
    file.close(); // 关闭文件

    // 获取文件信息
    QFileInfo info(filePath);
    qDebug() << "文件名称：" << info.fileName().toUtf8().data();
    qDebug() << "文件后缀：" << info.suffix();
    qDebug() << "文件大小：" << info.size() / 1024 / 1024;
    qDebug() << "文件创建时间："
             << info.birthTime().toString("yyyy-MM-dd hh:mm:ss");
  }
}

void Widget::on_writeButton_clicked() {
  QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "../",
                                                  "TXT(*.txt)"); // 读取文件路径
  if (fileName.isEmpty() == false) {
    QFile file;                                  // 创建文件对象
    file.setFileName(fileName);                  // 关联文件名字
    qDebug() << fileName;
    bool isOk = file.open(QIODevice::WriteOnly); // 打开文件，只写模式
    if (isOk) {
      QString str = ui->textEdit->toPlainText(); // 获取文本框内容
      // QString -> QByteArray
      //            file.write(str.toUtf8());  // 写文件，utf-8格式

      // QString -> string -> char *
      //            file.write(str.toStdString().data());   //
      //            保存的文件也是utf-8格式

      // 转换为本地编码
      file.write(str.toLocal8Bit());

      // QString -> QByteArray
      QString buf = "123";
      QByteArray arr = buf.toUtf8(); // 中文
      arr = buf.toLocal8Bit();       // 本地编码

      // QByteArray -> char *
      char *b = arr.data();

      // char * -> QString
      char *p = "abc";
      QString c = QString(p);
    }
    file.close();
  }
}
