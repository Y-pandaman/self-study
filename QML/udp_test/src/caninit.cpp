#include "caninit.h"

CanInit::CanInit(QObject *parent) : QObject(parent)
{
    socket_ = new QUdpSocket(this);
}

CanInit::~CanInit()
{
    file_.close();
}

// 实例化，用于与qml交互
CanInit *CanInit::getInstance()
{
    static CanInit * obj = new CanInit();
    return obj;
}

void CanInit::receiveData(QString remote_ip, int remote_port, int local_port){
    remote_ip_ = remote_ip;
    remote_port_ = remote_port;
    local_port_ = local_port;

    //     程序中bind某个IP/PORT之后，再次调用bind会失败
    //    在bind之前，先关掉socket，再重开socket
    socket_->close();
    socket_->open(QIODevice::ReadWrite);
    if(!socket_->bind(QHostAddress::AnyIPv4, local_port_))
        qDebug() << "无法监听本地UDP端口:" << QHostAddress::AnyIPv4 << local_port_;
    socket_->bind(QHostAddress::AnyIPv4, local_port_);

    //     CANET设置为UDP_SERVER模式时需要先发数据，才能接收到数据，此时本地绑定的端口不起作用
    //    QByteArray baData;
    //    QString msg="hello!";
    //    baData= msg.toLatin1();
    //    socket_->writeDatagram( baData ,QHostAddress(remote_ip_), remote_port_);

    connect(socket_, &QUdpSocket::readyRead, this, &CanInit::dealMsg);
}

void CanInit::dealMsg()
{
    qint64 len = socket_->readDatagram(buf_, sizeof(buf_), &cliAddr, &remote_port_);
    if(len > 0) {
        QString str = QString("[%1:%2] %3").arg(cliAddr.toString()).arg(remote_port_).arg(buf_);
    }
    else {
    }

    if(flag_){
        messageAnalysis(buf_, sizeof(buf_));
        //        emit btnStatus("停止接收");
    }
    else {
        //        emit btnStatus("开始接收");
    }

}

/**
 * @brief 解析udp数据
 *
 * @param buf udp缓冲区数据
 * @param len 数据长度
 */
void CanInit::messageAnalysis(char *buf, size_t len)
{
    size_t can_frame_size = 0;
    if(len % 13 == 0) {
        can_frame_size = len / 13;
    }
    else {
        LOG_F(WARNING, "buf length: %ld", len);
        return;
    }
    LOG_F(INFO, "can_size: %ld, long:  %ld", can_frame_size, len);

    for(size_t i = 0; i < can_frame_size; i++) {
        buf += i * 13;
        if((buf[0] & 0x30) == 0x00) {  // 四五RESVD位必须为0
            can_msgs canFrame;
            convertUdp2Can(buf, &canFrame);
            canAnalysis(&canFrame);
        }
        else {
            LOG_F(WARNING, "received data, but not can frame!");
        }
    }
}


/**
 * @brief 分解can帧
 *
 * @param data udp数据
 * @param can_message  can帧
 */
void CanInit::convertUdp2Can(char *data, can_msgs *can_message)
{
    can_message->data_len = data[0] & 0x0f;  // &0x0f取低四位

    Uint32_bytes id{};
    id.bytes[0]     = data[4];
    id.bytes[1]     = data[3];
    id.bytes[2]     = data[2];
    id.bytes[3]     = data[1];
    can_message->id = id.data;

    can_message->is_rtr      = data[0] & 0x40;  // 数据帧|远程帧
    can_message->is_extended = data[0] & 0x80;  // 扩展帧

    for(uint8_t i = 0; i < can_message->data_len; i++) {
        can_message->data[i] = data[i + 5];
    }
}


/**
 * @brief 检测can帧是否有数据
 *
 * @param can_frame can帧
 * @return true
 * @return false
 */
bool CanInit::isAllZeroValues(const can_msgs *can_frame)
{
    for(uint8_t i = 0; i < can_frame->data_len; i++) {
        if(can_frame->data[i] != 0)
            return false;
    }
    LOG_F(WARNING, "received a can frame 0x%x, but ALL ZERO! not process",
          can_frame->id);
    return true;
}


/**
 * @brief 解析can帧
 *
 * @param can_frame can帧
 */
void CanInit::canAnalysis(const can_msgs *can_frame)
{
    if(isAllZeroValues(can_frame)) {
        return;
    }
    LOG_F(INFO, "received can frame from CANET: 0x%x", can_frame->id);

    if(!file_.isOpen()){
        file_.open(QIODevice::Append);
    }

    // 保存数据
    m_dataStr = QString("%1%2").arg("0x").arg(QString::number(can_frame->id, 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->is_rtr, 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->is_extended, 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->data[0], 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->data[1], 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->data[2], 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->data[3], 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->data[4], 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->data[5], 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->data[6], 16)) + "," +
            QString("%1%2").arg("0x").arg(QString::number(can_frame->data[7], 16)) + "\r\n";
    emit sendData();
    file_.write(m_dataStr.toLatin1(), m_dataStr.length());

    switch(can_frame->id) {
    case 0x11223344:
        LOG_F(INFO, "success");
        LOG_F(INFO, "0x11223344 data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",
              can_frame->data[0], can_frame->data[1], can_frame->data[2],
                can_frame->data[3], can_frame->data[4], can_frame->data[5],
                can_frame->data[6], can_frame->data[7]);
        break;
    case 0x181:
        LOG_F(INFO, "0x181 data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",
              can_frame->data[0], can_frame->data[1], can_frame->data[2],
                can_frame->data[3], can_frame->data[4], can_frame->data[5],
                can_frame->data[6], can_frame->data[7]);
        break;
    case 0x281:
        LOG_F(INFO, "0x281 data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",
              can_frame->data[0], can_frame->data[1], can_frame->data[2],
                can_frame->data[3], can_frame->data[4], can_frame->data[5],
                can_frame->data[6], can_frame->data[7]);
        break;
    case 0x381:
        LOG_F(INFO, "0x381 data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",
              can_frame->data[0], can_frame->data[1], can_frame->data[2],
                can_frame->data[3], can_frame->data[4], can_frame->data[5],
                can_frame->data[6], can_frame->data[7]);
        break;

    default:
        break;
    }
}

void CanInit::createFile(QString filePath)
{
    #ifdef _WIN32
        fileName_ = QString::fromStdString(filePath.toStdString().substr(8,filePath.length())) + m_fileName + ".csv";  // 截取字符串
    #endif

    if (fileName_.isEmpty() == false) {
        file_.setFileName(fileName_);
        fileIsOK_ = file_.open(QIODevice::WriteOnly);
        file_.write("id,is_rtr,is_extended,data0,data1,data2,data3,data4,data5,data6,data7\n");
        //        file_.close();
    }

}

void CanInit::setFlag(bool flag)
{
    flag_ = flag;
    if(!false){
        file_.close();
    }
}

void CanInit::updateData(){

}
