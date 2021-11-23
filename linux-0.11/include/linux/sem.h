#ifndef _SEM_H
#define _SEM_H

#include <linux/sched.h>

#define SEM_NAME_LEN 32                /* 信号量名称最大长度 */
typedef struct sem_t{
    char name[SEM_NAME_LEN];        /* 信号量名称 */
    unsigned int value;                /* 信号量的值 */
    struct task_struct *s_wait;        /* 等待信号量的进程的pcb指针 */
    struct sem_t *next;                /* 用于连接信号量形成链表 */
}sem_t;

//sem_t *sem_open(const char *name, unsigned int value);    /* 打开或新建信号量 *//
//int sem_wait(sem_t *sem);            /* 等待信号量至其值大于0，将其值减1；对应P原语 */
//int sem_post(sem_t *sem);            /* 唤醒在信号量上等待的进程，将信号量值加1；对应V原语 */
//int sem_unlink(const char *name);    /* 销毁信号量 */

#endif
