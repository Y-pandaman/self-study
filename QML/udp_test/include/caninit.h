#ifndef CANINIT_H
#define CANINIT_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>
#include <QHostAddress>

#include "loguru.hpp"
#include <fstream>
#include <QFile>
#include "utils.h"

class CanInit : public QObject
{
    Q_OBJECT
    BJ_PROPERTY(QString, fileName);
    BJ_PROPERTY(QString, dataStr);

public:
    explicit CanInit(QObject *parent = nullptr);
    ~CanInit();
    static CanInit * getInstance();
    void dealMsg();
    void messageAnalysis(char *buf, size_t len);
    void convertUdp2Can(char *data, can_msgs *can_message);
    bool isAllZeroValues(const can_msgs *can_frame);
    void canAnalysis(const can_msgs *can_frame);

signals:
    void sendData();

public slots:
    void receiveData(QString remote_ip, int remote_port, int local_port);
    void updateData();
    void setFlag(bool flag);
    void createFile(QString filePath);

private:
    QUdpSocket *socket_;
    QString local_ip_, remote_ip_;
    quint16 local_port_, remote_port_;
    QHostAddress cliAddr;
    char buf_[26] = {0};
    bool flag_ = true;
    QString fileName_;
    QFile file_;
    bool fileIsOK_;
};

#endif // CANINIT_H
