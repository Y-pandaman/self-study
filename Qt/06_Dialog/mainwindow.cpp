#include "mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

  QMenuBar *mBar = menuBar();
  setMenuBar(mBar);
  QMenu *menu = mBar->addMenu("对话框");

  QAction *dialog = menu->addAction("模态对话框");
  connect(dialog, &QAction::triggered, [=]() {
    QDialog dlg;
    dlg.exec(); // 阻塞，对话框一直都在
    qDebug() << "***";
  });

  QAction *noDialog1 = menu->addAction("非模态对话框1");
  connect(noDialog1, &QAction::triggered, []() {
    QDialog dlg1;
    dlg1.show(); // 生命周期短，对话框不显示，如果要显示，就放到构造函数内
    qDebug() << "******";
  });

  QAction *noDialog2 = menu->addAction("非模态对话框2");
  connect(noDialog2, &QAction::triggered, [=]() {
    dlg2.show(); // 对话框显示，就把dlg2当做类的成员
    qDebug() << "*********";
  });

  QAction *noDialog3 = menu->addAction("非模态对话框3");
  connect(noDialog3, &QAction::triggered, [=]() {
    QDialog *dlg3 =
        new QDialog(this); // 对话框显示，创建一个空间，但是不自动释放，不推荐
    dlg3->show();
    qDebug() << "************";
  });

  QAction *noDialog4 = menu->addAction("非模态对话框4");
  connect(noDialog4, &QAction::triggered, [=]() {
    QDialog *dlg4 = new QDialog;
    dlg4->setAttribute(Qt::WA_DeleteOnClose); // 推荐
    dlg4->show();
    qDebug() << "***************";
  });

  QAction *aboutDialog = menu->addAction("关于对话框");
  connect(aboutDialog, &QAction::triggered,
          [=]() { QMessageBox::about(this, "关于", "关于Qt"); });

  QAction *questionDialog1 = menu->addAction("问题对话框1");
  connect(questionDialog1, &QAction::triggered, [=]() {
    int ret = QMessageBox::question(this, "问题", "Are you OK?");
    switch (ret) {
    case QMessageBox::Yes:
      qDebug() << "I am OK";
      break;
    case QMessageBox::No:
      qDebug() << "I am bad";
      break;
    default:
      break;
    }
  });

  QAction *questionDialog2 = menu->addAction("问题对话框2");
  connect(questionDialog2, &QAction::triggered, [=]() {
    int ret =
        QMessageBox::question(this, "问题", "Are you OK?", QMessageBox::Save,
                              QMessageBox::Cancel); // 后面可选
    switch (ret) {
    case QMessageBox::Save:
      qDebug() << "Saved";
      break;
    case QMessageBox::Cancel:
      qDebug() << "Canceled";
      break;
    default:
      break;
    }
  });

  QAction *fileDialog1 = menu->addAction("文件对话框1");
  connect(fileDialog1, &QAction::triggered, [=]() {
    QString path = QFileDialog::getOpenFileName(this, "打开文件", "../");
    qDebug() << path;
  });

  QAction *fileDialog2 = menu->addAction("文件对话框2");
  connect(fileDialog2, &QAction::triggered, [=]() {
    QString path = QFileDialog::getOpenFileName(
        this, "打开文件", "../",
        "source(*.cpp *.h);;Text(*.txt);;all(*.*)"); // 可选文件格式
    qDebug() << path;
  });
}

MainWindow::~MainWindow() {}
