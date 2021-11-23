#include <linux/sem.h>
#include <linux/kernel.h>
#include <asm/system.h>
//#include <linux/sched.h>
#include <asm/segment.h>
#include <unistd.h>

sem_t *sem_head = &((sem_t *){"\0", 0, NULL, NULL});    /* 链表头结点，方便统一操作 */

/* 将用户态中的ustr复制到内核态的kstr */
static inline int str_u2k(const char *ustr, char *kstr, unsigned int length)
{
    char c;
    int i;

    for(i=0; (c=get_fs_byte(ustr++))!='\0' && i<length; i++)
        *(kstr+i)=c;
    *(kstr+i)='\0';

    return i;
}


sem_t *sys_sem_open(const char *name, unsigned int value)
{
    sem_t *sem_cur, *sem_pre;
    char pname[SEM_NAME_LEN];

    /* 将用户态参数name指向的信号量名称拷贝到内核态指针pname中 */
    str_u2k(name, pname, SEM_NAME_LEN);

    /* 遍历链表，检验信号量是否已存在 */
    for(sem_pre=sem_head, sem_cur=sem_head->next; sem_cur && strcmp(pname, sem_cur->name);
            sem_pre=sem_cur, sem_cur=sem_cur->next);

    /* sem_cur为空，表明信号量不存在，分配一块内存新建一个信号量 */
    if(!sem_cur)
    {
        printk("semaphore %s no found. created a new one. \n", pname);
        sem_cur = (sem_t *)malloc(sizeof(sem_t));
        strcpy(sem_cur->name, pname);
        sem_cur->value = value;
        sem_cur->next = NULL;
        sem_pre->next = sem_cur;
    }
    printk("pid %d opens semaphore %s(value %u) OK. \n", current->pid, pname, sem_cur->value);
    return sem_cur;
}

int sys_sem_wait(sem_t *sem)
{
    cli();    /* 关闭中断 */
    /* 进程等待直到信号量的值大于0 */
    while(sem->value<=0)
        sleep_on(&(sem->s_wait));
    sem->value--;
    sti();    /* 开启中断 */
    return 0;
}

int sys_sem_post(sem_t *sem)
{
    sem->value++;
    /* 唤醒在信号量上等待的进程 */
    if(sem->s_wait)
    {
        wake_up(&(sem->s_wait));
        return 0;
    }
    return -1;
}

int sys_sem_unlink(const char *name)
{
    sem_t *sem_cur, *sem_pre;
    char pname[SEM_NAME_LEN];
    int i;

    str_u2k(name, pname, SEM_NAME_LEN);

    for(sem_pre=sem_head, sem_cur=sem_head->next; sem_cur && strcmp(pname, sem_cur->name);
            sem_pre=sem_cur, sem_cur=sem_cur->next);

    /* 找不到则返回错误代码-1 */
    if(!sem_cur)
        return -1;

    /* 找到了将其从链表中移除，并释放空间 */
    sem_pre->next = sem_cur->next;
    free(sem_cur);
    printk("unlink semaphore %s OK. \n", pname);
    return 0;
}
