#include "clientwidget.h"
#include "serverwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ServerWidget server_widget;
  server_widget.show();

  ClientWidget client_widget;
  client_widget.show();
  return a.exec();
}
