#ifndef CBASEPACKET_H
#define CBASEPACKET_H

#include <iostream>

class CBasePacket
{
public:
    CBasePacket(int size);
    ~CBasePacket();
    virtual int pack()=0;
    virtual int unpack()=0;
    char *getData(); //获取的数据
    unsigned int getSize(); //获取包长度

protected:
    char *m_data;
    unsigned m_size;
};

#endif // CBASEPACKET_H
