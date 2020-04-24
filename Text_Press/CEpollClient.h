#ifndef CEPOLLCLIENT_H
#define CEPOLLCLIENT_H
#include <QDebug>
#include "Base/CEpollBase.h"
#include "TcpSocket.h"
#include <string>
#include <unordered_set>
#include <QString>
#include "../common/NetPacket/NetPacket.h"
//管理所有模拟客户端类
using namespace std;
class CEpollClient : public CEpollBase
{
public:
    CEpollClient(int sum,CHostAddress myaddr,unsigned int maxEvent = 20,int timeout = -1);
    unordered_set<int> client_fd;//保存所有客户端fd
    int connectSucces;//连接成功数
    int RecvSum;//收到的包数量
    int RecvSumFail;//收到的不完整包数量
    void startNewConnect();//启动连接
    PacketBase *heart;    //心跳包
    ~CEpollClient();
protected:
    int ClientSum;
    CHostAddress addr;
    virtual void OnNewConnection();//建立新连接数
    virtual void OnReadData(int fd);
    virtual void OnClientClose(int fd);
    void Run(int nevent);
};

#endif // CEPOLLCLIENT_H
