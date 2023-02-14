#ifndef WIDGET_H
#define WIDGET_H

#include <QSqlTableModel>
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

private slots:
  void on_addButton_clicked();

  void on_sureButton_clicked();

  void on_cancelButton_clicked();

  void on_deleteButton_clicked();

  void on_searchButton_clicked();

private:
  Ui::Widget *ui;
  QSqlTableModel *tableModel;
};
#endif // WIDGET_H
