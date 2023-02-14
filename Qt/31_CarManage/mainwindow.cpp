#include "mainwindow.h"
#include "domxml.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  on_actionCar_triggered(); // 开始，进入车辆管理页面

  connectDB(); // 打开数据库

  initData(); // 初始化数据

  DomXML::createXML("../31_CarManage/demo.xml"); // 创建一个xml文件

//    QStringList list;
//    list << "二汽神龙"
//         << "毕加索"
//         << "39"
//         << "1"
//         << "39";
//    DomXML::appendXML("../31_CarManage/demo.xml", list);
}

MainWindow::~MainWindow() { delete ui; }

// 车辆管理菜单
void MainWindow::on_actionCar_triggered() {
  // 切换到车辆管理界页面
  ui->stackedWidget->setCurrentWidget(ui->car);
  ui->labelTitle->setText("车辆管理");
}

// 销售统计菜单
void MainWindow::on_actioncal_triggered() {
  // 切换到销售统计页面
  ui->stackedWidget->setCurrentWidget(ui->cal);
  ui->labelTitle->setText("销售统计");
}

// 连接数据库
void MainWindow::connectDB() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
  // 连接数据库
  db.setHostName("127.0.0.1"); // 数据库服务器ip
  db.setUserName("root");      // 数据库用户名
  db.setPassword("123456");    //密码
  db.setDatabaseName("car");   //使用哪个数据库

  // 打开数据库
  if (!db.open()) {
    QMessageBox::warning(this, "错误", db.lastError().text());
    return;
  }
}

// 初始化数据
void MainWindow::initData() {
  QSqlQueryModel *queryModel = new QSqlQueryModel(this); // 新建模型
  queryModel->setQuery("select name from factory");      // 查询语句
  ui->comboBoxFactory->setModel(queryModel);             // 跟下拉框绑定

  ui->labelLast->setText("0");          // 剩余数量
  ui->lineEditTotal->setEnabled(false); // 金额
}

// 厂家下拉框槽函数
void MainWindow::on_comboBoxFactory_currentIndexChanged(const QString &arg1) {
  if (arg1 == "请选择厂家") {
    // 所有内容清空
    ui->comboBoxBrand->clear();  // 品牌
    ui->lineEditPrice->clear();  // 报价
    ui->lineEditTotal->clear();  //金额
    ui->labelLast->setText("0"); //剩余数量
    ui->spinBox->setValue(0);    // 数量选择框
    ui->spinBox->setEnabled(false);
    ui->buttonSure->setEnabled(false);
  } else {
    ui->comboBoxBrand->clear();
    QSqlQuery query;
    QString sql =
        QString("select name from brand where factory = '%1' ").arg(arg1);
    query.exec(sql); // 执行sql语句
    // 获取内容
    while (query.next()) {
      QString name = query.value(0).toString();
      ui->comboBoxBrand->addItem(name);
    }
  }
}

// 品牌下拉框槽函数
void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &arg1) {
  QSqlQuery query;
  QString sql = QString("select price, last from brand where factory = '%1' "
                        "and name = '%2' ")
                    .arg(ui->comboBoxFactory->currentText())
                    .arg(arg1);
  query.exec(sql); // 执行sql语句

  // 获取内容
  while (query.next()) {
    int price = query.value("price").toInt();           // 报价
    int last = query.value("last").toInt();             // 剩余数量
    ui->lineEditPrice->setText(QString::number(price)); // 把整型转成字符型
    ui->labelLast->setText(QString::number(last));
  }
  ui->spinBox->setEnabled(true);
}

// 数量选择框槽函数
void MainWindow::on_spinBox_valueChanged(int arg1) {
  QString factory = ui->comboBoxFactory->currentText();
  QString brand = ui->comboBoxBrand->currentText();

  if (arg1 > 0) {
    ui->buttonSure->setEnabled(true);
  } else {
    ui->buttonSure->setEnabled(false);
  }

  // 获取数据库中的剩余数量
  QSqlQuery query;
  QString sql =
      QString("select last from brand where factory = '%1' and name = '%2'")
          .arg(factory)
          .arg(brand);
  query.exec(sql);

  int last = 0;
  while (query.next()) {
    last = query.value("last").toInt();
  }

  if (arg1 > last) { // 判断选择的数量是否大于剩余数量
    ui->spinBox->setValue(last);
    return;
  }

  int num = last - arg1;
  ui->labelLast->setText(QString::number(num)); // 更新剩余数量

  int price = ui->lineEditPrice->text().toInt();
  int total_price = price * arg1;
  ui->lineEditTotal->setText(QString::number(total_price)); //总价
}

void MainWindow::on_buttonCancel_clicked() {
  //    on_comboBoxFactory_currentIndexChanged("请选择厂家");
  ui->comboBoxFactory->setCurrentIndex(0);
}

void MainWindow::on_buttonSure_clicked() {
  int num = ui->spinBox->value();           // 销售数量
  int last = ui->labelLast->text().toInt(); // 剩余数量

  // 获取数据库的销量
  QSqlQuery query;
  QString sql =
      QString("select sell from brand where factory = '%1' and name = '%2'")
          .arg(ui->comboBoxFactory->currentText())
          .arg(ui->comboBoxBrand->currentText());
  query.exec(sql);

  int sell = 0;
  while (query.next()) {
    sell = query.value("sell").toInt();
  }

  // 更新数据库
  sell += num;
  sql = QString("update brand set sell = %1, last = %2 where factory = '%3' "
                "and name = '%4'")
            .arg(sell)
            .arg(last)
            .arg(ui->comboBoxFactory->currentText())
            .arg(ui->comboBoxBrand->currentText());
  query.exec(sql);

  // 把确认后的数据，更新到xml中
  QStringList list;
  list << ui->comboBoxFactory->currentText() << ui->comboBoxBrand->currentText()
       << ui->lineEditPrice->text() << QString::number(num)
       << ui->lineEditTotal->text();
  DomXML::appendXML("../31_CarManage/demo.xml", list); // 将记录添加到XML文件中

  QStringList factoryList;
  QStringList brandList;
  QStringList priceList;
  QStringList numList;
  QStringList totalList;
  DomXML::readXML("../31_CarManage/demo.xml", factoryList, brandList, priceList,
                  numList, totalList);
  for (int i = 0; i < factoryList.size(); i++) {
    QString str = QString("%1:%2卖出了%3,单价为:%4,总价为:%5")
                      .arg(factoryList.at(i))
                      .arg(brandList.at(i))
                      .arg(numList.at(i))
                      .arg(priceList.at(i))
                      .arg(totalList.at(i));

    ui->textEdit->append(str);
  }

  ui->buttonSure->setEnabled(false);
  on_buttonCancel_clicked();
}
