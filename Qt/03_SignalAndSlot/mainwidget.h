#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "subwidget.h"
#include <QPushButton>
#include <QWidget>

class MainWidget : public QWidget {
  Q_OBJECT

public:
  MainWidget(QWidget *parent = nullptr);
  ~MainWidget();

  void mySlot();
  void changeWidget();
  void dealSubWidget();
  void dealSlot(int, QString);

private:
  QPushButton button1;
  QPushButton *button2;
  QPushButton button3;

  SubWidget sub_widget;
};
#endif // MAINWIDGET_H
