#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // 绘图设备 400*300
  QPixmap pixmap(400, 300);
  QPainter painter(&pixmap); // 指定绘图设备piamap
//  painter.fillRect(0, 0, 400, 300, QBrush(Qt::white));  // 通过画布填充颜色
  pixmap.fill(Qt::white);  // 通过绘图设备填充颜色
  painter.drawPixmap(0, 0, 80, 90, QPixmap("../image/3.png"));
  pixmap.save("../image/pixmap.png");  // 保存图片
}

Widget::~Widget() { delete ui; }
