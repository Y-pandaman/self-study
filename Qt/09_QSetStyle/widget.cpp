#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  //    ui->label->setStyleSheet("QLabel{color:red;}");

  // 窗体内所有的label都是此样式
  this->setStyleSheet("QLabel{"
                      "color:rgb(0, 100, 255);" // 字体颜色
                      "background-color:red;"   // 背景色
                      "}");

  // 特定label的样式
  ui->label->setStyleSheet(
      "QLabel{"
      "color:rgb(0, 100, 255);" // 字体颜色
      "background-color:green;" // 背景色
      //                                              "background-image:url(://image/gif.gif);"
      //                                              // 背景图，自动平铺
      "border-image:url(://image/gif.gif);" // 背景图，自适应大小
      //                                              "border-image:url(://image/gif.gif)
      //                                              30 30 30 30 stretch
      //                                              stretch;"  //
      //                                              背景图，自适应大小,图片裁剪
      "}");

  // 伪状态
  ui->pushButton->setStyleSheet(
      "QPushButton{"
      "border: 2px outset green;"
      "border-image: url(://image/ntp.png);" //默认背景图
      "}"
      "QPushButton:hover{" // 鼠标位于控件上
      "border-image:url(://image/nvr.png);"
      "}"
      "QPushButton:pressed{" // 鼠标点击控件
      "border-image:url(://image/gif.gif);"
      "}");
}

Widget::~Widget() { delete ui; }
