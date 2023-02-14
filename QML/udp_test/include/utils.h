#ifndef UTILS_H
#define UTILS_H

#include "stdint.h"

// 自定义属性宏
#define BJ_PROPERTY(type,name)\
Q_PROPERTY(type name READ name WRITE set##name NOTIFY name##Changed)\
public:\
void set##name(type temp##name)\
{\
    if(m_##name == temp##name)\
        return;\
    m_##name = temp##name;\
    emit name##Changed();\
}\
type name()\
{\
    return m_##name;\
}\
Q_SIGNALS:\
    void name##Changed(); \
private:\
    type m_##name;


struct can_msgs {
    uint32_t id;
    uint8_t data_len;
    uint8_t data[8];
    bool is_rtr;
    bool is_extended;
};

union Uint32_bytes {
    uint32_t data;
    uint8_t bytes[4];
};

class Utils
{
public:
    Utils();
};

#endif // UTILS_H
