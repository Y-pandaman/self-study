#include "mywidget.h"

// Qt头文件没有.h
#include <QApplication> // 应用程序类

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // MyWidget是一个窗口类
  MyWidget w;

  // 窗口创建默认是隐藏的，需要人为显示
  w.show();

  // 让程序一直执行，等待用户操作
  return a.exec();
}
