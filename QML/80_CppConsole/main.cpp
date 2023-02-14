#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString message("hello world !!!");
    QFile file(QDir::home().absoluteFilePath("out.txt"));
    if(!file.open(QIODevice::WriteOnly)) {
            qWarning( "cannot open file") ;
            return -1;
    }
    QTextStream stream(&file);
    stream << message;
    return 0;
}
