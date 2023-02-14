

# Qt

## 1 QtTest

- `QApplication a(argc, argv)` 应用程序类

- `MyWidget w` MyWidget是一个窗口类
- `w.show()` 窗口创建默认是隐藏的，需要人为显示
- `rentun a.exec` 程序一直执行，等待用户操作

## 2 HelloQt

- 设置窗口标题 `setWindowTitle(QString("窗体1"))`
- 指定父对象 `setParent(&w2)`

## 3 SignalAndSlot

### 头文件

```
#include <QDebug> // 打印
#include <QPushButton>
```

-  &button1:信号发出者，指针类型

- &QpushButton::pressed:处理的信号，&发送者的类名::信号名

-  this: 信号接收者

- &MainWidget::close : 槽函数，信号处理函数  &接收的类名::槽函数名

```
  connect(&button1, &QPushButton::pressed, this, &MainWidget::close);
```

- 自定义槽
  - 任意的成员函数
  - 普通全局函数
  - 静态函数
  - Lambda表达式

- 槽函数需要与信号一致（参数，返回值）
- 信号和槽都没有返回值，可以有参数
- 重载信号会有二义性，使用函数指针

## 4 QtCoordinate

- 对于父窗口（主窗口），坐标系统相对于屏幕
  原点：屏幕左上角
  x:从左向右
  y:从上向下

- 子窗口，坐标系统相对于父窗口
  原点：窗口空白区域左上角，不包括边框
  x:从左向右
   y:从上向下
  
- 
  指定父对象后，子对象如果是动态分配空间的new,不需要手动释放delete，系统会自动释放
  

## 5 QMainWindow

### 头文件

```
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
```

## 6 Dialog

### 头文件

```
#include <QAction>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
```

- 模态对话框 ，会阻塞，对话框一直都在

- 非模态对话框

  ```
  QDialog *dlg4 = new QDialog;
  dlg4->setAttribute(Qt::WA_DeleteOnClose);  // 推荐
  ```

## 7 Designor

### 头文件

```
#include <QCompleter> // 提示模型
#include <QDebug>
#include <QMovie> // 动画
#include <QPushButton>
#include <QStringList> // 列表
```

## 8 Layout

### 头文件

```
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
```

- 滑条（垂直、水平）
- 弹簧（垂直、水平）

## 9 QSetStyle

- 样式表

  ```
  // 窗体内所有的label都是此样式
  this->setStyleSheet("QLabel{"
                        "color:rgb(0, 100, 255);" // 字体颜色
                        "background-color:red;"   // 背景色
                        "}");
  ```

- 伪状态

  ```
  ui->pushButton->setStyleSheet(
        "QPushButton{"
        "border: 2px outset green;"
        "border-image: url(://image/ntp.png);" //默认背景图
        "}"
        "QPushButton:hover{" // 鼠标位于控件上
        "border-image:url(://image/nvr.png);"
        "}"
        "QPushButton:pressed{" // 鼠标点击控件
        "border-image:url(://image/gif.gif);"
        "}");
  ```

## 10 QEvent

### 头文件

```
#include <QCloseEvent>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>
```

- html语句

  ```
  // 居中显示
  QString str = QString("<center><h1>鼠标点击坐标:(%1, %2)</h1></center>").arg(i).arg(j);
  this->setText(str);
  ```

- 键盘按下事件 `keyPressEvent(QKeyEvent *ev)`
- 定时器事件 `timerEvent(QTimerEvent *ev)`
- 鼠标按下事件 `mousePressEvent(QMouseEvent *ev)`
- 关闭事件 `closeEvent(QCloseEvent *ev)`
- 事件过滤器 `event(QEvent *e)`

## 11 PaintEvent

### 头文件

```
#include <QPainter> // 画布
#include <QPen>     // 画笔
```

- 创建画布对象 `Qpainter painter`，或` QPainter painter(this)`
- 指定当前窗口为绘图设备，`begin(this)`
- 绘图操作
  - 设置背景图 `drawPixmap()`
  - 创建画笔  `QPen pen`
  - 设置线宽、颜色、风格 `setWidth`,`setColor`,`setStyle`
  - 画笔给画布 `setPen()`
  - 创建画刷 `QBrush brush`
  - 设置颜色、样式  `setColor`,`setStyle`
  - 画刷给画布 `setBrush()`
  - 画直线、矩形、圆形、圆脸 	`drawLine`,`drawRect`,`drawEllipse`,`drawPixmap`
- 结束绘图，`end()`

## 12 QBitMap

### 头文件

```
#include <QPainter>
#include <QBitmap>
```

- 创建画布 `Qpainter painter(this)`
- pixmap画图 `painter.drawPixmap(0, 0, QPixmap("../image/1.png"))`
- bitmap画图 `painter.drawPixmap(0, 0, QBitmap("../image/1.png"))`
- pixmap
  - 创建pixmap `QPixmap pixmap`
  - 加载图片 `pixmap.load()`
  - 画图 `painter.drawPixmap()`
- bitmap
  - 创建bitmap `QBitmap bitmap`
  - 加载图片 `bitmap.load()`
  - 画图 `painter.drawPixmap()`

## 绘图设备

QPixmap：针对屏幕进行了优化，和平台相关，不能对图片进行修改

QImage：和平台无关，可以对图片进行像素修改，在线程中绘图

QPicture：保存绘图的状态（二进制文件）

## 13 QPixMap

```
#include <QPainter>
```

- 指定画布大小 `QPixmap pixmap(400, 300)`
- 指定绘图设备 `QPainter painter(&pixmap)`
- 填充颜色
  - 通过画布填充：`painter.fillRect()`
  - 通过绘图设备填充：`pixmap.fill()`
- 画图 `drawPixmap()`
- 保存图片 `pixmap.save()`

## 14 QImage

### 头文件

```
#include <QImage>
#include <QPainter>
```

- 创建绘图设备,透明 `QImage image(400, 300, QImage::Format_ARGB32)`
- 创建画布 `QPainter painter`
- 开始绘图 `painter.begin(&image)`
- 画图 `drawImage()`
- 修改，给像素赋值 image.setPixel(QPoint(x,y),qRgb(255,0,0))
- 获取像素值 image.pixel(QPoint(x,y))
- 结束绘图  `painter.end()`
- 保存图片 `pixmap.save()`

## 15 QPicture

### 头文件

```
#include <QPainter>
#include <QPicture>
```

- 创建绘图设备 `QPicture picture`

- 创建画布 `QPainter painter`

- 开始绘图 `painter.begin(&picture)`

- 画图 `drawPixmap`

- 结束绘图  `painter.end()`

- 保存二进制文件 `picture.save()`

- 查看图片

  ```
  QPicture pic;
  // pic.load("../image/picture.bin");
  pic.load("../image/picture.png");
  QPainter painter(this);
  painter.drawPicture(0, 0, pic);
  ```

- QPixmap 转成 QImage

  ```
  QPainter painter(this);
  QPixmap pixmap;
  pixmap.load("../image/3.png");
  QImage tempImage = pixmap.toImage();
  painter.drawImage(0, 0, tempImage);
  ```

- QImage 转成 QPixmap

  ```
  QPainter painter(this);
  QImage image;
  image.load("../image/3.png");
  QPixmap tempPixmap = QPixmap::fromImage(image);
  painter.drawPixmap(200,0,tempPixmap);
  ```

  ## 16 IrregularWidget不规则窗口

  ### 头文件

  ```
  #include <QMouseEvent>
  #include <QPainter>
  ```

- 去窗口边框 `setWindowFlag(Qt::FramelessWindowHint)`
- 窗口背景设置为透明 `setAttribute(Qt::WA_TranslucentBackground)`
- 求坐标差值 `point = event->globalPos() - this->frameGeometry().topLeft()`

- 移动窗口

  ```
  if (event->buttons() & Qt::LeftButton) {
      move(event->globalPos() - point);
    }
  ```

## 17 QFile

### 头文件

```
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
```

### 读文件

- 打开路径 

  ```
  QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "../", "TXT(*.txt)")
  ```

- 创建文件对象 `QFile file(filePath)`

- 只读模式打开文件 	`file.open(QIODevice::ReadOnly)`

- 读文件

  - `QByteArray array = file.readAll(); // 读文件，默认只识别utf-8，一次性读取`

  - ` array += file.readLine(); // 按行读`

- 关闭文件 `file.close()`

- 获取文件信息 `QFileInfo info(filePath)`
  - 文件名 `info.fileName().toUtf8().data()`
  - 文件后缀 `info.suffix()`
  - 文件大小 `info.size() / 1024 / 1024`
  - 文件创建时间 `info.birthTime().toString("yyyy-MM-dd hh:mm:ss")`

### 写文件

- 读取文件路径 `

  ```
  QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "../","TXT(*.txt)") 
  ```

- 创建文件对象 `QFile file`

- 关联文件名 `file.setFileName(fileName)`

- 只读模式打开 `file.open(QIODevice::WriteOnly)`

- 写文件

  - ```
    file.write(str.toUtf8())  // utf-8编码
    ```

  - ```
    file.write(str.toStdString().data())  // utf-8编码
    ```

  - ```
    file.write(str.toLocal8Bit()) // 本地编码
    ```

- 关闭文件 `file.close()`

## 18 QDataStream

### 头文件

```
#include <QDataStream>
#include <QFile>
#include <QDebug>
```

### 宏定义

```
// 用cout 代替qDeubg(),并输出文件名和所在行号
#define cout qDebug() << "[" << __FILE__ << ":" <<__LINE__ << "]"
```

### 写文件

- 创建文件对象 `QFile file("../txt/stream.txt")`
- 只读方式打开 `file.open(QIODevice::WriteOnly)`
- 创建数据流，和file文件关联 `QDataStream dataStream(&file)`
- 写文件 `dataStream << QString("主要看气质") << 250`
- 关闭文件 `file.close()`

### 读文件

- 创建文件对象 `QFile file("../txt/stream.txt")`
- 只读方式打开 `file.open(QIODevice::ReadOnly)`
- 创建数据流，和file文件关联 `QDataStream dataStream(&file)`

- 按写文件的顺序读文件 `dataStream >> str >> num`
- 关闭文件 `file.close()`

## 19 QTextStream

### 头文件

```
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
```

### 宏定义

```
// 用cout 代替qDeubg(),并输出文件名和所在行号
#define cout qDebug() << "[" << __FILE__ << ":" <<__LINE__ << "]"
```

### 写文件

- 创建文件对象 

  ```
  QFile file;        // 创建文件对象
  file.setFileName("../txt/textstream.txt");  // 设置文件名
  ```

- 只读方式打开 `file.open(QIODevice::WriteOnly)`

- 创建数据流，和file文件关联 `QTextStream textaStream(&file)`

- 写文件 `textStream << QString("主要看气质") << 250`

- 写文件 `textStream << QString("主要看气质") << " " << 250`

- 关闭文件 `file.close()`

### 读文件

- 创建文件对象 

  ```
  QFile file;               // 创建文件对象
  file.setFileName("../txt/textstream.txt");  // 设置文件名
  ```

- 只读方式打开 `file.open(QIODevice::ReadOnly)`

- 创建数据流，和file文件关联 `QTextStream textStream(&file)`

- 按写文件的顺序读文件 `dataStream >> str >> num`
- 关闭文件 `file.close()`

## 20 QBuffer

### 头文件

```
#include <QBuffer> // 内存文件
#include <QDataStream>
#include <QDebug>
```

- 创建内存文件

  ```
  // 方式1
  QByteArray array;
  QBuffer memFile(&array);
  ```

  ```
  // 方式2
  QBuffer memFile;

- 只读方式打开文件 `memFile.open(QIODevice::WriteOnly)`

- 写文件 `memFile.write()`

- 关闭文件 `close()`

- 输出 `qDebug() << memFile.buffer()`,`qDebug() << array`

```
// 用datastream方式读写
QBuffer memFile1;
memFile1.open(QIODevice::WriteOnly);
QDataStream stream(&memFile1);
stream << QString("测试") << 250;
memFile1.close();
qDebug() << memFile1.buffer();

memFile1.open(QIODevice::ReadOnly);
QDataStream out;
out.setDevice(&memFile1);
QString str;
int num;
out >> str >> num;
memFile1.close();
qDebug() << str.toUtf8().data() << num;
```

## 21 TCP

### 头文件

```
#include <QDateTime> // 时间
#include <QTcpServer> // 监听套接字
#include <QTcpSocket> //通信套接字
```

### 服务端

- 创建监听套接字 `tcpServer = new QTcpServer(this)`

- 设置监听ip和端口号 `tcpServer->listen(QHostAddress::Any, 8080)`

- 建立连接 `QTcpServer::newConnection`

  - 获取客户端ip和端口 `tcpSocket->peerAddress().toString()`,`tcpSocket->peerPort()`

  - 获取内容 

    ```
    connect(tcpSocket, &QTcpSocket::readyRead, [=]() {
        QByteArray array = tcpSocket->readAll();});
    ```

- 发送数据 `tcpSocket->write(str.toUtf8().data())`
- 断开连接 

```
tcpSocket->disconnectFromHost();  // 断开连接
tcpSocket->close();
tcpSocket = nullptr;
```

### 客户端

- 创建套接字  `tcpSocket = new QTcpSocket(this)`

- 建立连接 `tcpSocket->connectToHost(ip, port)`

- 获取内容 

  ```
   connect(tcpSocket, &QTcpSocket::readyRead, [=]() {
      QByteArray array = tcpSocket->readAll();};
  ```

- 发送内容 `tcpSocket->write(str.toUtf8().data())`

- 断开连接

  ```
  tcpSocket->disconnectFromHost(); // 主动断开连接
  tcpSocket->close();
  ```

## 22 UDP

### 头文件

```
#include <QHostAddress>
#include <QDateTime>
#include <QUdpSocket>  // UDP套接字
```

- 创建套接字 `udpSocket = new QUdpSocket(this)`
- 绑定端口  `udpSocket->bind(8080)`
- 接收数据 `udpSocket->readDatagram(buf, sizeof(buf), &ip, &port)`
- 发送数据 `udpSocket->writeDatagram(str.toUtf8().data(), QHostAddress(ip), port)`

## 23 QTImer

### 头文件

```
#include <QTimer> // 定时器
```

- 创建定时器对象 `new QTimer(this)`

- 启动定时器 `timer->start(100)`，触发 `timeout()`

- 处理事件

  ```
  connect(timer, &QTimer::timeout, [=]() {
      static int i = 0;
      ui->lcdNumber->display(++i);
    });
  ```

- 停止定时器 `timer->stop()`

## 24 TCPFile

### 头文件

```
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
```

### 服务端

- 创建套接字 `tcpServer = new QTcpServer(this)`

- 监听端口 `tcpServer->listen(QHostAddress::Any, 8080)`

- 建立连接 

  ```
  connect(tcpServer, &QTcpServer::newConnection,[=](){
        // 取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        // 获取ip和port
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
    });
  ```

- 选择文件 `QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "../")`

- 发送头信息

  ```
  QString fileHead  = QString("%1##%2").arg(fileName).arg(fileSize);
  tcpSocket->write(fileHead.toUtf8());
  ```

- 启动定时器（防止黏包）`timer.start(200)`

- 发送文件

  ```
  char buf[4096] = {0};  // 每次发送数据的大小
  len = file.read(buf, sizeof(buf)); // 往文件中读数据
  len = tcpSocket->write(buf,len); // 发送数据，读多少，发多少
  ```

- 关闭文件 `file.close()`

- 断开客户端

  ```
  tcpSocket->disconnectFromHost();
  tcpSocket->close();
  ```

### 客户端

- 创建套接字 `tcpSocket = new QTcpSocket(this)`
- 建立连接 `tcpSocket->connectToHost(QHostAddress(ip), port)`

- 解析头信息

  ```
  fileName = QString(buf).section("##", 0, 0);
  fileSize = QString(buf).section("##", 1, 1).toInt();
  ```

- 接收文件数据 `file.write(buf)`

- 关闭文件  `file.close()`

- 断开连接

  ```
  tcpSocket->disconnectFromHost();
  tcpSocket->close();
  ```

## 25 QThread

### 头文件

```
#include <QThread>
#include <QDebug>
```

- 创建线程类，继承于QThread `class MyThread : public QThread`

- 新建虚函数`run()`，在`run()`中处理另一个线程的工作
- 创建线程 `thread = new MyThread(this)`

- 启动线程 `thread->start()`

- 停止线程 

   ```
   thread->quit();  // 停止线程
   thread->wait(); // 等待线程处理完工作
   ```

## 26 ThreadPro

### 头文件

```
#include <QThread>
#include <QDebug>
```

- 创建自定义线程类，继承于QObject `class MyThread : public QObject`
- 自定义线程，不能指定父对象 `myThread = new MyThread`

- 创建子线程 `thread = new QThread(this)`
- 把自定义的线程加入到子线程中 `myThread->moveToThread(thread)`

- 启动线程，通过信号与槽调用线程处理函数

  ```
  thread->start();
  emit startThread();
  ```

- 线程处理函数中设置标志位

- 通过标志位关闭线程

  ```
  myThread->setFlag(true);
  // 只写quit和wait，线程退出不了
  thread->quit();
  thread->wait();
  ```

## 27 ThreadImage

### 头文件

```
#include <QImage>
#include <QThread>
#include <QBrush>
#include <QPainter>
#include <QPen>
#include "mythread.h" // 自定义类
```

- 自定义类对象，不指定父对象 `myThread = new MyThread`

- 创建子线程 `thread = new QThread(this)`

- 把自定义模块添加到子线程 `myThread->moveToThread(thread)`

- 启动子线程 `thread->start()`

- 通过信号与槽调用线程处理函数

  ```
  connect(ui->pushButton, &QPushButton::pressed, myThread,
            &MyThread::drawImage);
  connect(myThread, &MyThread::updateImage, this, &Widget::getImage);
  ```

- 关闭线程

  ```
  thread->quit();
  thread->wait();
  delete myThread;
  ```

## 28 Database

### 头文件

```
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase> // 数据库
#include <QSqlError>  // 数据库报错
#include <QSqlQuery> //数据库查询
#include <QVariantList>  // 排列
```

- 添加数据库 `QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL")`

- 连接数据库

  ```
  db.setHostName("127.0.0.1"); // 数据库服务器ip
  db.setUserName("root");      // 数据库用户名
  db.setPassword("123456");    //密码
  db.setDatabaseName("info");  //使用哪个数据库
  ```

- 打开数据库 `db.open()`

- 创建查询对象 `QSqlQuery query`

- 执行sql语句 `query.exec("`create table student(id int primary key auto_increment, name varchar(255), age int, score int)`")`

- 批量插入 `QVariantList nameList`
- 查询 `query.exec("select * from student")`
- 开始事务  `QSqlDatabase::database().transaction()`
- 确定删除 `QSqlDatabase::database().commit()`
- 回滚 `QSqlDatabase::database().rollback()`

## 29 SqlLite

### 头文件

```
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase> // 数据库
#include <QSqlError>    // 数据库报错
#include <QSqlQuery>    //数据库查询
#include <QVariantList> // 排列
```

- 添加数据库 `QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE")`
- 连接数据库 `db.setDatabaseName("../info.db")`
- 打开数据库 `db.open()`
- 创建查询对象 `QSqlQuery query`
- 执行sql语句 `query.exec("`create table student(id int primary key auto_increment, name varchar(255), age int, score int)`")`

- 批量插入 `QVariantList idList, nameList, ageList, scoreList`
- 查询 `query.exec("select * from student")`

## 30 ModelView

### 头文件

```
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord> // 记录类
#include <QSqlTableModel>
```

- 连接数据库

- 设置模型 `tableModel = new QSqlTableModel(this)`

- 指定模型使用哪个表 `tableModel->setTable("student")`

- 把模型放进tableview控件中显示 `ui->tableView->setModel(tableModel)`

- 显示数据 `tableModel->select()`

- 设置编辑策略，手动提交修改 `tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit)`

- 添加空记录

  ```
  QSqlRecord record = tableModel->record(); // 获取空记录
  int row = tableModel->rowCount();         // 获取行号
  tableModel->insertRecord(row, record);    // 插入空行
  ```

- 提交动作 `tableModel->submitAll()`

- 取消动作

  ```
  tableModel->revertAll(); // 取消所有动作
  tableModel->submitAll(); // 提交动作
  ```

- 删除所选行的数据

  ```
  // 获取选中的模型
  QItemSelectionModel *sModel = ui->tableView->selectionModel();
  QModelIndexList list = sModel->selectedRows(); // 取出模型中的索引
  // 删除所有选中的行
  for (int i = 0; i < list.size(); i++) {
    tableModel->removeRow(list.at(i).row());
  }
  ```

- 设置过滤条件

  ```
  tableModel->setFilter(str)
  ```

