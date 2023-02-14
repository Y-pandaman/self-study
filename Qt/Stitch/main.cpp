#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("stitch image");
    w.show();
    return a.exec();
}
