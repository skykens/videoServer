#ifndef CBASESTREAM_H
#define CBASESTREAM_H

#pragma once

#include "HostAddress.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


class CBaseStream
{
public:
    CBaseStream();
    CBaseStream(int fd);//普通构造
   ~CBaseStream(void);
    void SetFd(int fd);
    int GetFd() const;
    int Read(char *buf, const int buf_len);
    int Readn(char *buf, const int buf_len);
    int Recv(char *buf, const int buf_len);
    int Write(const char *buf, const int buf_len);
private:
    int m_fd;
};

#endif // CBASESTREAM_H
