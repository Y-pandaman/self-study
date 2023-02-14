#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  void dataWrite();
  void dataRead();

private slots:
  void on_writeButton_clicked();

private:
  Ui::Widget *ui;
};
#endif // WIDGET_H
