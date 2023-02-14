#include "mywidget.h"

#include <QCloseEvent>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>

#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QLabel(parent), ui(new Ui::MyWidget) {
  ui->setupUi(this);
  timerId = this->startTimer(100); // 启动定时器  毫秒为单位
  this->timerId2 = this->startTimer(500);

  connect(ui->pushButton, &MyButton::clicked,
          [=]() { qDebug() << "button is pressed!"; });

  // 安装事件过滤器
  ui->label_2->installEventFilter(this);

  ui->label_2->setMouseTracking(true); // 鼠标自动有效
}

MyWidget::~MyWidget() { delete ui; }

void MyWidget::keyPressEvent(QKeyEvent *ev) {
  qDebug() << (char)ev->key();

  if (ev->key() == Qt::Key_A) {
    qDebug() << "Qt::Key_A";
  }
}

void MyWidget::timerEvent(QTimerEvent *ev) {
  if (ev->timerId() == this->timerId) {
    static int sec = 0;
    ui->label->setText(
        QString("<center><h1>timer out: %1</h1></center>").arg(sec++));

    if (sec == 50) {
      this->killTimer(this->timerId);
    }
  }
  else if (ev->timerId() == this->timerId2) {
    static int sec = 0;
    ui->label_2->setText(
        QString("<center><h1>timer out: %1</h1></center>").arg(sec++));
  }
}

void MyWidget::mousePressEvent(QMouseEvent *ev) { qDebug() << "++++++++"; }

void MyWidget::closeEvent(QCloseEvent *ev) {
  int ret = QMessageBox::question(this, "question", "是否需要关闭窗口");
  if (ret == QMessageBox::Yes) {
    // 关闭窗口
    // 处理关闭窗口事件，接收事件，事件就不会继续传递
    ev->accept();
  }
  else {
    // 不关闭窗口
    // 忽略事件，事件继续传递给父组件
    ev->ignore();
  }
}

bool MyWidget::event(QEvent *e) {
  // 事件分发
  //    switch ( e->type() ) {
  //        case QEvent::Close:
  //            closeEvent(e);
  //            break;
  //        case QEvent::MouseMove:
  //            mouseMoveEvent(e);
  //            break;
  //    }
  if (e->type() == QEvent::Timer) {
    // 关闭定时器
    // 如果返回true,事件停止传播

    //        QTimerEvent *env = static_cast<QTimerEvent*>(e);  // 转换类型
    //        timerEvent(env);

    return true;
  }
  else if (e->type() == QEvent::KeyPress) {
    QKeyEvent *env = static_cast<QKeyEvent *>(e);
    if (env->key() == Qt::Key_B) {
      return QWidget::event(e);
    }
    return true;
  }
  else {
    return QWidget::event(e);
  }
}

bool MyWidget::eventFilter(QObject *obj, QEvent *e) {
  if (obj == ui->label_2) {
    QMouseEvent *env = static_cast<QMouseEvent *>(e);
    // 判断事件
    if (e->type() == QEvent::MouseMove) {
      ui->label_2->setText(
          QString("Mouse move:(%1, %2)").arg(env->x()).arg(env->y()));
      return true; // 不让事件继续传播
    }
    else if (e->type() == QEvent::MouseButtonPress) {
      ui->label_2->setText(
          QString("Mouse press:(%1, %2)").arg(env->x()).arg(env->y()));
    }
    else if (e->type() == QEvent::MouseButtonRelease) {
      ui->label_2->setText(
          QString("Mouse release:(%1, %2)").arg(env->x()).arg(env->y()));
    }
    else {
      return QWidget::eventFilter(obj, e);
    }
  }
  else {
    return QWidget::eventFilter(obj, e);
  }

  if (obj == ui->pushButton) {
  }
}
