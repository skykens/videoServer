#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "ShmFIFO.h"
#define ERR_EXIT(m) \
    do { \
            perror(m); \
            fprintf(stderr, "Err: (%s:%s:%d)", __FILE__, __func__, __LINE__); \
            exit(EXIT_FAILURE); \
    } while(0)


typedef struct shmhead_st
{
        int shmid;			// 共享内存ID

    unsigned int blksize;		// 块大小
    unsigned int blocks;		// 总块数
    unsigned int rd_index;		// 读索引
    unsigned int wr_index;		// 写索引

        //必须放在共享内存内部才行
        sem_t sem_mutex;	// 用来互斥用的信号量
        sem_t sem_full;		// 用来控制共享内存是否满的信号量
        sem_t sem_empty;	// 用来控制共享内存是否空的信号量

}shmhead_t;
CShmFIFO *CShmFIFO::m_recvFIFO=NULL;
CShmFIFO *CShmFIFO::m_sendFIFO=NULL;
CShmFIFO::CShmFIFO(int key, int blksize, int blocks)
{
    this->open(key, blksize, blocks);
}

CShmFIFO::CShmFIFO()
{
    m_shmhead = NULL;
    m_payload = NULL;
    m_open = false;
}

CShmFIFO *CShmFIFO::GetinterfaceRecv(int key,int blksize,int blocks)
{
    if(m_recvFIFO==NULL)
    {
        m_recvFIFO=new CShmFIFO(key,blksize,blocks);

    }
    return m_recvFIFO;
}

CShmFIFO *CShmFIFO::GetinterfaceSend(int key,int blksize,int blocks)
{
    if(m_sendFIFO==NULL)
    {
        m_sendFIFO=new CShmFIFO(key,blksize,blocks);

    }
    return m_sendFIFO;
}

CShmFIFO::~CShmFIFO()
{
    this->close();
}

//返回头地址
bool CShmFIFO::init(int key, int blksize, int blocks)
{
    int shmid = 0;

    //1. 查看是否已经存在共享内存，如果有则删除旧的
    shmid = shmget((key_t)key, 0, 0);
    if (shmid != -1)
    {
        shmctl(shmid, IPC_RMID, NULL); 	//	删除已经存在的共享内存
    }

    //2. 创建共享内存
    shmid = shmget((key_t)key, sizeof(shmhead_t) + blksize*blocks, 0666 | IPC_CREAT | IPC_EXCL);
    if(shmid == -1)
    {
        ERR_EXIT("shmget");
    }
   // printf("Create shmid=%d size=%u \n", shmid, sizeof(shmhead_t) + blksize*blocks);

    //3.连接共享内存
    m_shmhead = shmat(shmid, (void*)0, 0);					//连接共享内存
    if(m_shmhead == (void*)-1)
    {
        ERR_EXIT("shmat");
    }
    memset(m_shmhead, 0, sizeof(shmhead_t) + blksize*blocks);		//初始化

    //4. 初始化共享内存信息
    shmhead_t * pHead = (shmhead_t *)(m_shmhead);
    pHead->shmid	= shmid;				//共享内存shmid
    pHead->blksize	= blksize;			//共享信息写入
    pHead->blocks	= blocks;				//写入每块大小
    pHead->rd_index = 0;					//一开始位置都是第一块
    pHead->wr_index = 0;					//
    sem_init(&pHead->sem_mutex, 1, 1);	// 第一个1表示可以跨进程共享，第二个1表示初始值
    sem_init(&pHead->sem_empty, 1, 0);	// 第一个1表示可以跨进程共享，第二个0表示初始值
    sem_init(&pHead->sem_full, 1, blocks);// 第一个1表示可以跨进程共享，第二个blocks表示初始值

    //5. 填充控制共享内存的信息
    m_payload = (char *)(pHead + 1);	//实际负载起始位置
    m_open = true;

    return true;
}

void CShmFIFO::destroy()
{
    shmhead_t *pHead = (shmhead_t *)m_shmhead;
    int shmid = pHead->shmid;

    //删除信号量
    sem_destroy (&pHead->sem_full);
    sem_destroy (&pHead->sem_empty);
    sem_destroy (&pHead->sem_mutex);
    shmdt(m_shmhead); //共享内存脱离

    //销毁共享内存
    if(shmctl(shmid, IPC_RMID, 0) == -1)		//删除共享内存
    {
        printf("delete shmid=%d \n", shmid);
        ERR_EXIT("shmctl rm");
    }

    m_shmhead = NULL;
    m_payload = NULL;
    m_open = false;
}

void CShmFIFO::Destroy(int key)
{
    int shmid = 0;

    //1. 查看是否已经存在共享内存，如果有则删除旧的
    shmid = shmget((key_t)key, 0, 0);
    if (shmid != -1)
    {
        printf("delete shmid=%d \n", shmid);
        shmctl(shmid, IPC_RMID, NULL); 	//	删除已经存在的共享内存
    }
}

//返回头地址
bool CShmFIFO::open(int key, int blksize, int blocks)
{

    int shmid;  //

    this->close();

    //1. 查看是否已经存在共享内存，如果有则删除旧的
    shmid = shmget((key_t)key, 0, 0);
    if (shmid == -1)
    {
        return this->init(key, blksize, blocks);
    }
  //  printf("Create shmid=%d size=%u \n", shmid, sizeof(shmhead_t) + blksize*blocks);

    //2.连接共享内存
    m_shmhead = shmat(shmid, (void*)0, 0);					//连接共享内存
    if(m_shmhead == (void*)-1)
    {
        ERR_EXIT("shmat");
    }

    //3. 填充控制共享内存的信息
    m_payload = (char *)((shmhead_t *)m_shmhead + 1);	//实际负载起始位置
    m_open = true;

    return true;

}

void CShmFIFO::close(void)
{
    if(m_open)
    {
        shmdt(m_shmhead); //共享内存脱离
        m_shmhead = NULL;
        m_payload = NULL;
        m_open = false;
    }
}

void CShmFIFO::write(const void *buf)
{

    shmhead_t *pHead = (shmhead_t *)m_shmhead;

    sem_wait(&pHead->sem_full);				//是否有资源写？	可用写资源-1
    sem_wait(&pHead->sem_mutex);				//是否有人正在写？
    //printf("write to shm[%d] index %d \n", pHead->shmid, pHead->wr_index);
    //memset(m_payload + (pHead->wr_index) * (pHead->blksize), 0, pHead->blksize);
    memcpy(m_payload + (pHead->wr_index) * (pHead->blksize), buf, pHead->blksize);
    pHead->wr_index = (pHead->wr_index+1) % (pHead->blocks);	//写位置偏移
    sem_post(&pHead->sem_mutex);				//解除互斥
    sem_post(&pHead->sem_empty);				//可用读资源+1
}

void CShmFIFO::read(void *buf)
{
    shmhead_t *pHead = (shmhead_t *)m_shmhead;

    sem_wait(&pHead->sem_empty);				//检测写资源是否可用
    //sem_wait(&pHead->sem_mutex);
    //memset(buf, 0, sizeof(buf));
    //printf("read from shm[%d] index %d \n", pHead->shmid, pHead->rd_index);
    memcpy(buf, m_payload + (pHead->rd_index) * (pHead->blksize), pHead->blksize);
    //memset(m_payload + (pHead->rd_index) * (pHead->blksize), 0, pHead->blksize);
    //读位置偏移
    pHead->rd_index = (pHead->rd_index+1) % (pHead->blocks);
    //sem_post(&pHead->sem_mutex);				//解除互斥
    sem_post(&pHead->sem_full);					//增加可写资源
}

