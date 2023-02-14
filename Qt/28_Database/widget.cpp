#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase> // 数据库
#include <QSqlError>  // 数据库报错
#include <QSqlQuery> //数据库查询
#include <QVariantList>  // 排列

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  //  qDebug() << QSqlDatabase::drivers(); // 打印qt支持的数据库驱动

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

  QSqlQuery query;

  // 新建数据表
  // query.exec("create table student(id int primary key auto_increment, name
  // varchar(255), age int, score int);"); // 数据库语言

  // 插入数据
  // query.exec("insert into student(id, name, age, score) values(1, 'mike', 19,
  // 68);");

  // 批量插入

  //  // odbc风格,？相当于占位符
  //  query.prepare("insert into student(name, age, score) values( ?, ?, ?);");
  //  //预处理
  //  // 给字段设置内容 list
  //  QVariantList nameList;
  //  nameList << "小二" << "小三" << "小四";
  //  QVariantList ageList;
  //  ageList << 18 << 19 << 19;
  //  QVariantList scoreList;
  //  scoreList << 75 << 56 << 77;

  //  // 给字段绑定相应的值， 按顺序绑定
  //  query.addBindValue(nameList);
  //  query.addBindValue(ageList);
  //  query.addBindValue(scoreList);

  //  // 执行预处理命令
  //  query.execBatch();

  //  // oracle风格  占位符  :+自定义名
  //  query.prepare("insert into student(name, age, score) values(:name, :age,
  //  :score);"); //预处理
  //    // 给字段设置内容 list
  //    QVariantList nameList1;
  //    nameList1 << "小五" << "小六" << "小七";
  //    QVariantList ageList1;
  //    ageList1 << 18 << 18 << 19;
  //    QVariantList scoreList1;
  //    scoreList1 << 74 << 53 << 56;

  //    // 给字段绑定值, 不必按顺序绑定
  //    query.bindValue(":name", nameList1);
  //    query.bindValue(":age", ageList1);
  //    query.bindValue(":score", scoreList1);

  //    // 执行预处理命令
  //    query.execBatch();

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

void Widget::on_deleteButton_clicked() {
  // 获取行编辑内容
  QString name = ui->lineEdit->text();
  // 组sql语句
  QString sql_str = QString("delete from student where name = '%1'").arg(name);

  // 开始一个事务
  QSqlDatabase::database().transaction();
  QSqlQuery query;
  query.exec(sql_str);
}

void Widget::on_sureButton_clicked() {
  // 确定删除
  QSqlDatabase::database().commit();
}

void Widget::on_cancelButton_clicked() {
  // 回滚
  QSqlDatabase::database().rollback();
}
