#include "ShmFIFO.h"

ShmFIFO::ShmFIFO(int key, int blksize, int blocks)
{
    this->m_open = false;
    this->m_shmhead = NULL;
    this->m_payload = NULL;
    open(key,blksize,blocks);
}

ShmFIFO::ShmFIFO()
{
    this->m_open = false;
    this->m_shmhead = NULL;
    this->m_payload = NULL;
}

ShmFIFO::~ShmFIFO()
{
    destroy();
}

bool ShmFIFO::init(int key, int blksize, int blocks)
{
    //1. create shared memory
    int shmid = shmget((key_t)key,0,0);
    if(shmid != -1)
    {
        shmctl(shmid,IPC_RMID,NULL);
    }
    shmid = shmget((key_t)key,SHM_HEAD_LEN+blksize*blocks,IPC_CREAT|0666|IPC_EXCL);
    if(shmid == -1)
    {
        return false;
    }
    //2. 连接上去返回shmaddr

    this->m_shmhead = shmat(shmid,(void *)0,0);
    if(m_shmhead == (void *)-1)
    {
        perror("shmat");
    }
    //3. 初始化信息（信息头head=shmaddr）
    //包括blocks blocks shmid rd=0 wr=0
    //mutex=1, full(可读资源个数=0)，empty(可写资源个数=blocks)
    shmhead_t *p_shmhead = (shmhead_t *)m_shmhead;

    p_shmhead->shmid = shmid;
    p_shmhead->blksize = blksize;
    p_shmhead->blocks = blocks;
    p_shmhead->rd_index = 0;
    p_shmhead->wr_index = 0;

    sem_init(&(p_shmhead->sem_mutex),1,1);
    sem_init(&(p_shmhead->sem_full),1,blocks);
    sem_init(&(p_shmhead->sem_empty),1,0);

    //4. malloc fifo 进程控制头shmfifo_t*,初始化p_shmhead=shmaddr , p_payload=p_shmhead+1
    this->m_payload = (char *)(p_shmhead+1);
    this->m_open = true;
    return true;
}

void ShmFIFO::destroy(void)
{
    shmhead_t *pHead = (shmhead_t *)m_shmhead;
    int shmid = pHead->shmid;

    //删除信号量
    sem_destroy (&pHead->sem_full);
    sem_destroy (&pHead->sem_empty);
    sem_destroy (&pHead->sem_mutex);
    shmdt(pHead); //共享内存脱离

    //销毁共享内存
    if(shmctl(shmid, IPC_RMID, 0) == -1)		//删除共享内存
    {
        ERR_EXIT("shmctl rm");
    }
}

void ShmFIFO::Destroy(int key)
{
    int shmid = shmget((key_t)key,0,0);
    if(shmid != -1)
    {
        shmctl(shmid,IPC_RMID,NULL);
    }
}

bool ShmFIFO::open(int key, int blksize, int blocks)
{
    // 1.判断是否存在shm，没有则创建
    int shmid = shmget((key_t)key,0,0);
    if(shmid == -1)
    {
        init(key, blksize, blocks);
        return true;
    }
    // 2. 存在则shmat, 返回shmaddr
    this->m_shmhead = shmat(shmid,NULL,0);
    if(m_shmhead == (void *)-1)
    {
        perror("shmat");
    }
    // 3. malloc fifo, fifo->p_shmhead = shmaddr, p_payload = p_shmhead+1;
    shmhead_t *p_shmhead = (shmhead_t *)m_shmhead;
    this->m_payload = (char *)(p_shmhead+1);
    this->m_open = true;
    return true;
}

void ShmFIFO::close(void)
{
    shmhead_t *p_shmhead = (shmhead_t *)m_shmhead;
    shmdt(p_shmhead);
}

void ShmFIFO::write(const void *buf)
{
    shmhead_t *p_shmhead = (shmhead_t *)m_shmhead;
    //1. P(empty)
    //semaphore_p(fifo->p_shmhead->sem_empty);
    sem_wait(&(p_shmhead->sem_full));
    //2. 上锁P(mutex)
    //semaphore_p(fifo->p_shmhead->sem_mutex);
    sem_wait(&(p_shmhead->sem_mutex));
    //3. memcpy(p_payload+wr_index*blksize, buf, blksize);
    memcpy(this->m_payload+(p_shmhead->wr_index)*(p_shmhead->blksize),buf,p_shmhead->blksize);
    //4. wr_index = (++wr_index) % blocks
    p_shmhead->wr_index = (++p_shmhead->wr_index)%(p_shmhead->blocks);
    //5. 解锁V(mutex)
    //semaphore_v(fifo->p_shmhead->sem_mutex);
    sem_post(&(p_shmhead->sem_mutex));
    //6. V(full)
    //semaphore_v(fifo->p_shmhead->sem_full);
    sem_post(&(p_shmhead->sem_empty));
}

void ShmFIFO::read(void *buf)
{
    shmhead_t *p_shmhead = (shmhead_t *)m_shmhead;
    //1. P(full)
    //semaphore_p(fifo->p_shmhead->sem_full);
    sem_wait(&(p_shmhead->sem_empty));
    //2. 上锁P(mutex)
    //semaphore_p(fifo->p_shmhead->sem_mutex);
    sem_wait(&(p_shmhead->sem_mutex));
    //3. memcpy(buf. p_payload+rx_index*blksize, blksize);
    memcpy(buf,this->m_payload+(p_shmhead->rd_index)*(p_shmhead->blksize),p_shmhead->blksize);
    //4. rd_index = (++rd_index) % blocks
    p_shmhead->rd_index = (++p_shmhead->rd_index) % (p_shmhead->blocks);
    //5. 解锁V(mutex)
    sem_post(&(p_shmhead->sem_mutex));
    //6. V(empty)
    sem_post(&(p_shmhead->sem_full));
}
