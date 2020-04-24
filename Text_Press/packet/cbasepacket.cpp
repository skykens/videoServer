#include "cbasepacket.h"

CBasePacket::CBasePacket(int size) : m_size(size)
{
    m_data = new char[m_size];
}

CBasePacket::~CBasePacket()
{
    delete m_data;
}

char *CBasePacket::getData()
{
    return m_data;
}

unsigned int CBasePacket::getSize()
{
    return m_size;
}
