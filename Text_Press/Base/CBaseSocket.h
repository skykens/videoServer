#ifndef CBASESOCKET_H
#define CBASESOCKET_H

#pragma once

#include "CBaseStream.h"

class CBaseSocket
{
public:

    CBaseSocket();
    CBaseSocket(int type, int sin_farmly = AF_INET, int protocol = 0);
    ~CBaseSocket();
    int GetSocket() const { return m_fd;}
    void SetSocket(int fd);
    CHostAddress GetAddress();
    CHostAddress GetPeerAddress();
    bool Bind(CHostAddress hostaddr);
    bool Close();

protected:
    void Create(int sin_farmly,int flag,int protocl);
    int m_fd;
    CBaseStream m_stream;
};

#endif // CBASESOCKET_H
