#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCompleter> // 提示模型
#include <QDebug>
#include <QMovie> // 动画
#include <QPushButton>
#include <QStringList> // 列表

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->pushButton->setText("123");
  connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::close);

  // 获取行编辑文本框内容
  QString str = ui->lineEdit->text();
  qDebug() << str;
  // 设置内容
  ui->lineEdit->setText("465");

  // 设置内容显示间隙
  ui->lineEdit->setTextMargins(15, 0, 0, 0);

  // 设置内容显示方式 密码*形式
  //    ui->lineEdit->setEchoMode(QLineEdit::Password);

  // 设置列表
  QStringList list;
  list << "Hello"
       << "How Are You"
       << "Hi";

  // 设置提示模型
  QCompleter *com = new QCompleter(list, this);
  com->setCaseSensitivity(Qt::CaseInsensitive); // 不区分大小写

  ui->lineEdit->setCompleter(com);

  ui->labelText->setText("文字");                         // 设置文本
  ui->labelImage->setPixmap(QPixmap("://image/ntp.png")); // 设置图片
  ui->labelImage->setScaledContents(true);

  QMovie *myMovie = new QMovie("://image/gif.gif"); //  创建动画
  ui->labelGif->setMovie(myMovie);                  // 设置动画
  ui->labelGif->setScaledContents(true);            // 画面适应
  myMovie->start();                                 // 启动动画

  ui->labelUrl->setText(
      "<h1><a href=\"www.baidu.com\">百度一下</a></h1>"); // 显示网页超链接
  ui->labelUrl->setOpenExternalLinks(true); // 打开浏览器，显示超链接内容

  // 数码管
  ui->lcdNumber->display(123);

  // 进度条
  ui->progressBar->setMinimum(0);   // 设置最小值
  ui->progressBar->setMaximum(200); // 设置最大值
  ui->progressBar->setValue(100);   // 设置当前值
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_change_clicked() {
  static int i = 0;
  ui->stackedWidget->setCurrentIndex(++i % 3);
}
