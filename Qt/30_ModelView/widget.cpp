#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord> // 记录类

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  qDebug() << QSqlDatabase::drivers(); // 打印qt支持的数据库驱动

  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // 添加Mysql数据库
  // 连接数据库
  db.setHostName("127.0.0.1"); // 数据库服务器ip
  db.setUserName("root");      // 数据库用户名
  db.setPassword("123456");    //密码
  db.setDatabaseName("info");  //使用哪个数据库

  // 打开数据库
  if (!db.open()) {
    QMessageBox::warning(this, "错误", db.lastError().text());
    return;
  }

  // 设置模型
  tableModel = new QSqlTableModel(this);
  tableModel->setTable("student"); // 指定使用哪个表

  // 把模型放进view中
  ui->tableView->setModel(tableModel);

  // 显示数据库中的数据
  tableModel->select();

  // 更改第0列的标题展示方式，不更改数据库
  tableModel->setHeaderData(0, Qt::Horizontal, "学号");

  // 设置编辑策略：手动提交修改
  tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

  //   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //
  //   view中的数据库不允许修改
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_addButton_clicked() {
  // 添加空记录
  QSqlRecord record = tableModel->record(); // 获取空记录
  int row = tableModel->rowCount();         // 获取行号
  tableModel->insertRecord(row, record);    // 插入空行
}

void Widget::on_sureButton_clicked() {
  tableModel->submitAll(); // 提交动作
}

void Widget::on_cancelButton_clicked() {
  tableModel->revertAll(); // 取消所有动作
  tableModel->submitAll(); // 提交动作
}

void Widget::on_deleteButton_clicked() {
  // 获取选中的模型
  QItemSelectionModel *sModel = ui->tableView->selectionModel();
  QModelIndexList list = sModel->selectedRows(); // 取出模型中的索引
  // 删除所有选中的行
  for (int i = 0; i < list.size(); i++) {
    tableModel->removeRow(list.at(i).row());
  }
}

void Widget::on_searchButton_clicked() {
  QString name = ui->lineEdit->text();
  QString str = QString("name = '%1'").arg(name); // 查询的语句，字符串

  tableModel->setFilter(str); //设置过滤条件
  //  tableModel->select();
}
