#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase> // 数据库
#include <QSqlError>    // 数据库报错
#include <QSqlQuery>    //数据库查询
#include <QVariantList> // 排列

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  //  qDebug() << QSqlDatabase::drivers(); // 打印qt支持的数据库驱动

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // 添加sqlite数据库
  db.setDatabaseName("../info.db");

  // 打开数据库
  if (!db.open()) {
    QMessageBox::warning(this, "错误", db.lastError().text());
    return;
  }

  QSqlQuery query;

  // 新建数据表
  query.exec("create table student(id int primary key, name varchar(255), age "
             "int, score int);"); // 数据库语言

  // odbc风格,？相当于占位符
  query.prepare(
      "insert into student(id, name, age, score) values( ?, ?, ?, ?);");
  //预处理
  // 给字段设置内容 list
  QVariantList idList;
  idList << 1 << 2 << 3 << 4;
  QVariantList nameList;
  nameList << "小一"
           << "小二"
           << "小三"
           << "小四";
  QVariantList ageList;
  ageList << 18 << 19 << 19 << 18;
  QVariantList scoreList;
  scoreList << 75 << 56 << 77 << 89;

  // 给字段绑定相应的值， 按顺序绑定
  query.addBindValue(idList);
  query.addBindValue(nameList);
  query.addBindValue(ageList);
  query.addBindValue(scoreList);

  // 执行预处理命令
  query.execBatch();

  // 查找
  query.exec("select * from student");
  //  query.exec("select * from student where name = '小五'");
  while (query.next()) { // 一行一行遍历
    // 输出当前行的内容
    qDebug() << query.value(0).toInt() << query.value(1).toString()
             << query.value("age").toInt() << query.value("score").toInt();
  }
}

Widget::~Widget() {
    delete ui;
}
