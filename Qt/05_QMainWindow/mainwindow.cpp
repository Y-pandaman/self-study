#include "mainwindow.h"
#include <QAction> // 菜单项，添加动作
#include <QDebug>
#include <QDockWidget> //浮动窗口
#include <QLabel>      // 标签
#include <QMenu>       // 菜单
#include <QMenuBar>    // 菜单栏
#include <QPushButton> //按钮
#include <QStatusBar>  // 状态栏
#include <QTextEdit>   // 文本编辑区
#include <QToolBar>    // 工具栏

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  // 菜单栏
  QMenuBar *mBar = menuBar();

  // 添加菜单
  QMenu *pFile = mBar->addMenu("文件");

  // 添加菜单项,添加动作
  QAction *pNew = pFile->addAction("新建");
  connect(pNew, &QAction::triggered, [=]() { qDebug() << "pushdown button"; });

  pFile->addSeparator(); // 添加分割线
  QAction *pOpen = pFile->addAction("打开");

  // 工具栏,菜单项的快捷键
  QToolBar *toolBar = addToolBar("toolbar");
  //工具栏添加快捷键
  toolBar->addAction(pNew); // 引用菜单
  QPushButton *button = new QPushButton(this);
  button->setText("按钮1");
  //添加小控件
  toolBar->addWidget(button);
  connect(button, &QPushButton::clicked, [=]() { button->setText("123"); });

  // 状态栏
  QStatusBar *sBar = statusBar();
  QLabel *label = new QLabel(this);
  label->setText("Norm text file");
  sBar->addWidget(label);
  // addWidget 从左往右添加
  sBar->addWidget(new QLabel("2", this));
  sBar->addWidget(new QLabel("3", this));
  // addPermanentWidget从右往左添加
  sBar->addPermanentWidget(new QLabel("4", this));
  sBar->addPermanentWidget(new QLabel("5", this));

  // 文本编辑区
  QTextEdit *textEdit = new QTextEdit(this);
  setCentralWidget(textEdit);

  // 浮动窗口
  QDockWidget *dock = new QDockWidget(this);
  addDockWidget(Qt::RightDockWidgetArea,
                dock); // 放置的位置：右边：Qt::RightDockWidgetArea

  // 浮动窗口内添加文本编辑区
  QTextEdit *textEdit_dock = new QTextEdit(this);
  dock->setWidget(textEdit_dock);

  resize(500, 400);
}

MainWindow::~MainWindow() {}
