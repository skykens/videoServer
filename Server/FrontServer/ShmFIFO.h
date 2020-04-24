#ifndef _SHM_FIFO_H_
#define _SHM_FIFO_H_

#include <iostream>


class CShmFIFO 
{
public:
	CShmFIFO(int key, int blksize, int blocks);
	CShmFIFO();
    static CShmFIFO *GetinterfaceRecv(int key,int blksize,int blocks);
    static CShmFIFO *GetinterfaceSend(int key,int blksize,int blocks);
	virtual ~CShmFIFO();

	//创建和销毁
	bool init(int key, int blksize, int blocks);
	void destroy(void);
	static void Destroy(int key); //静态删除共享内存方法

	// 打开和关闭
	bool open(int key, int blksize, int blocks);
	void close(void);

	//读取和存储
	void write(const void *buf);
	void read(void *buf);


protected:

   static CShmFIFO* m_recvFIFO;
   static  CShmFIFO *m_sendFIFO;
	//进程控制信息块
	bool m_open;
	void *m_shmhead;		// 共享内存头部指针
	char *m_payload;			// 有效负载的起始地址
};


#endif /* _SHM_FIFO_H_ */
