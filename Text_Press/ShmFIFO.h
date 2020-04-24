#ifndef SHMFIFO_H
#define SHMFIFO_H

#include <iostream>
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
using namespace std;

#define SHMBLOCKSIZE 2048

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
    sem_t sem_mutex;		        // 用来互斥用的信号量，进行读写的时候上锁
    sem_t sem_full;				// 用来说明总共可以写的数据块，默认blocks
    sem_t sem_empty;			// 用来说明总共可以读的数据块，默认0

}shmhead_t;

//进程控制信息块
typedef struct shmfifo_st
{
    shmhead_t *p_shmhead;		// 共享内存头部指针
    char *p_payload;		// 有效数据的起始地址
}shmfifo_t;


#define SHM_FIFO_LEN sizeof(shmfifo_t)
#define SHM_HEAD_LEN sizeof(shmhead_t)

class ShmFIFO
{
public:
    ShmFIFO(int key, int blksize, int blocks);
    ShmFIFO();
    ~ShmFIFO();

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
    //进程控制信息块
    bool m_open;
    void *m_shmhead;		// 共享内存头部指针
    char *m_payload;			// 有效负载的起始地址
};

#endif // SHMFIFO_H
