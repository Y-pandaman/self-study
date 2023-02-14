#include <QApplication>
#include <QPushButton> // 按钮类
#include <QWidget>     // 窗口控件基类

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QWidget w;
  w.setWindowTitle(QString("窗体1")); // 设置标题
  w.show();

  // 没有指定父对象，对象和对象之间独立
  // a指定b为它的父对象，a放在b的上面
  // 指定父对象方式：
  // (1) setParent;
  // (2) 通过构造函数传参
  QPushButton button;
  button.setText("按钮1"); // 给按钮设置内容
  button.show();           // 显示按钮

  QWidget w2;
  w2.setWindowTitle(QString("窗体2"));
  QPushButton button2;
  button2.setText("按钮2");
  button2.setParent(&w2); // 指定父对象
  button2.move(100, 100); // 设置按钮的位置，左上角（0,0）

  QPushButton button3(&w2); // 通过构造函数传参
  button3.setText("按钮3");
  button3.move(200, 200);

  w2.show();

  return app.exec();
}
