#include "widget.h"
#include "ui_widget.h"
#include <QPainter> // 画家
#include <QPen>     // 画笔

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  x = 0;
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *) {
  //    QPainter painter(this);

  QPainter painter;    // 创建画家对象
  painter.begin(this); // 指定当前窗口为绘图设备
  // 绘图操作。。。
  //    painter.drawPixmap(0, 0, width(), height(),
  //    QPixmap("../image/ntp.png"));  // 设置背景图
  painter.drawPixmap(
      rect(), QPixmap("../image/PersonalFormBG.jpg")); // rect()自动获取窗体区域

  // 定义画笔
  QPen pen;
  pen.setWidth(5); // 设置线宽
                   //    pen.setColor(Qt::red); // 设置颜色
  pen.setColor(QColor(100, 100, 100));
  pen.setStyle(Qt::DashLine); // 设置风格，虚实线

  // 把画笔交给画家
  painter.setPen(pen);

  // 画直线
  painter.drawLine(50, 50, 150, 50); // 起点x，起点y，终点x，终点y
  painter.drawLine(50, 50, 50, 150);

  // 创建画刷对象
  QBrush brush;
  brush.setColor(Qt::red);           // 设置颜色
  brush.setStyle(Qt::Dense1Pattern); // 设置样式

  // 把画刷交给画家
  painter.setBrush(brush);

  // 画矩形
  painter.drawRect(150, 150, 100, 50); // 起点x，起点y，长度，宽度

  // 画圆形
  painter.drawEllipse(QPoint(400, 200), 50, 50); // 圆心，x，y

  // 画笑脸
  painter.drawPixmap(x, 200, 80, 90, QPixmap("../image/3.png"));  // 起点x，起点y，宽，高，图片路径

  painter.end();
}

void Widget::on_pushButton_clicked()
{
    x += 20;
    if(x > width()){
        x = 0;
    }

    update();  // 刷新窗口，让整个窗口重绘，间接调用paintevent
}
