#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  timer = new QTimer(this);

  connect(timer, &QTimer::timeout, [=]() {
    static int i = 0;
    ui->lcdNumber->display(++i);
  });
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_startButton_clicked() {
  if (!timer->isActive()) {
    timer->start(100); // 启动定时器，时间间隔为100 ms
  }
}

void Widget::on_stopButton_clicked() {
  if (timer->isActive()) {
    timer->stop(); // 停止定时器
  }
}
