#include "mythread.h"
#include <QBrush>
#include <QPainter>
#include <QPen>

MyThread::MyThread(QObject *parent) : QObject(parent) {}

void MyThread::drawImage() {
  QImage image(500, 500, QImage::Format_ARGB32); // 定义QImage绘图设备
  QPainter painter(&image); // 创建画布，指定绘图设备

  // 定义画笔
  QPen pen;
  pen.setWidth(5); // 宽度
  painter.setPen(pen);

  // 定义画刷
  QBrush brush;
  brush.setStyle(Qt::SolidPattern); // 样式
  brush.setColor(Qt::red);          // 颜色
  painter.setBrush(brush);

  // 定义5个点
  QPoint a[] = {
      QPoint(qrand() % 400, qrand() % 400),
      QPoint(qrand() % 400, qrand() % 400),
      QPoint(qrand() % 400, qrand() % 400),
      QPoint(qrand() % 400, qrand() % 400),
      QPoint(qrand() % 400, qrand() % 400),
  };

  painter.drawPolygon(a, 5); // 画多边形

  // 通过信号发送图片
  emit updateImage(image);
}
