#include "mainwidget.h"
#include <QDebug> // 打印
#include <QPushButton>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  button1.setParent(this);
  button1.setText("关闭");
  button1.move(100, 100);

  button2 = new QPushButton(this); // 指针分配空间
  button2->setText("按钮2");
  button2->move(200, 100);

  // &button1:信号发出者，指针类型
  // &QpushButton::pressed:处理的信号，&发送者的类名::信号名
  // this: 信号接收者
  // &MainWidget::close : 槽函数，信号处理函数  &接收的类名::槽函数名
  connect(&button1, &QPushButton::pressed, this, &MainWidget::close);

  // 自定义槽，普通函数的用法
  // Qt5:任意的成员函数，普通全局函数，静态函数，Lambda表达式
  // 槽函数需要与信号一致（参数，返回值）
  // 信号和槽都没有返回值,可以有参数
  connect(button2, &QPushButton::released, this, &MainWidget::mySlot);

  connect(button2, &QPushButton::released, &button1, &QPushButton::hide);

  setWindowTitle("窗口1");

  button3.setParent(this);
  button3.setText("切换到窗口2");
  button3.move(50, 50); // 按钮位置

  connect(&button3, &QPushButton::released, this, &MainWidget::changeWidget);

  // 处理窗口2的信号
  //    connect(&sub_widget, &SubWidget::mySignal, this,
  //    &MainWidget::dealSubWidget);

  // 重载信号会有二义性，使用函数指针
  void (SubWidget::*funSignal)() = &SubWidget::mySignal; // 不带参数
  connect(&sub_widget, funSignal, this, &MainWidget::dealSubWidget);

  void (SubWidget::*testSignal)(int, QString) = &SubWidget::mySignal; // 带参数
  connect(&sub_widget, testSignal, this, &MainWidget::dealSlot);

  // Lambda表达式  匿名函数对象，C++11增加的新特性
  //项目文件添加：  CONFIG += C++11
  // 配合信号一起使用
  QPushButton *button4 = new QPushButton(this);
  button4->setText("Lambda表达式");
  button4->move(200, 50);
  connect(button4, &QPushButton::released, []() { qDebug() << "11111"; });

  connect(button4, &QPushButton::released,
          [button4]() // 把button4传进去，可以在{}内操作button4的属性
          {
            button4->setText("变了");
            qDebug() << "11111";
          });

  int a = 10, b = 20;
  connect(button4, &QPushButton::released,
          //   [=] ： 把外部所有局部变量、类中所有成员以值传递
          // [this] : 类中所有成员以值传递
          // [&] : 把外部所有局部变量以值传递，外部有按钮等时，不要用&,用=
          [=]() mutable {
            button4->setText("变了");
            qDebug() << "11111";
            qDebug() << a << b;
            a = a + 1; // 只读属性，不能赋值，如果要改可以在（）后加mutable
          });

  connect(button4, &QPushButton::clicked,
          [=](bool isCheck) // clicked有参数，（）里也要带一个参数
          { qDebug() << isCheck; });

  resize(400, 300); // 重设窗体大小
}

void MainWidget::dealSlot(int a, QString str) {
  // str.toUtf8()  -> 字节数组QByteArray
  // .data()   ->  QByteArray  ->  char *
  qDebug() << a << str.toUtf8().data();
}

void MainWidget::mySlot() { button2->setText("我变了"); }

void MainWidget::changeWidget() {
  this->hide();      // 窗口1隐藏
  sub_widget.show(); // 窗口2显示
}

void MainWidget::dealSubWidget() {
  sub_widget.hide(); // 窗口2隐藏
  this->show();      // 窗口1显示
}

MainWidget::~MainWidget() {}
