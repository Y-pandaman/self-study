#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWidget widget; // 先执行MainWidget的构造函数
  widget.show();
  return app.exec();
}
