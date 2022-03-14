/*producer*/ 
#define __LIBRARY__
#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/sem.h>

_syscall2(sem_t *,sem_open,const char *,name,int,value);
_syscall1(int,sem_post,sem_t *,sem);
_syscall1(int,sem_wait,sem_t *,sem);

_syscall1(int, shmat, int, shmid);
_syscall2(int, shmget, unsigned int, key, size_t, size);

#define PRODUCE_NUM 200
#define BUFFER_SIZE 10
#define SHM_KEY 2018

int main(int argc, char* argv[])
{
    sem_t *Empty,*Full,*Mutex;    
    int i, shm_id, location=0;
    int *p;

    Empty = sem_open("Empty", BUFFER_SIZE);
    Full = sem_open("Full", 0);
    Mutex = sem_open("Mutex", 1);

    if((shm_id = shmget(SHM_KEY, BUFFER_SIZE*sizeof(int))) < 0)
        printf("shmget failed!");    

    if((p = (int * )shmat(shm_id)) < 0)
        printf("shmat error!");
    for(i=0; i<PRODUCE_NUM; i++)
    {
        sem_wait(Empty);
        sem_wait(Mutex);

        p[location] = i;

        sem_post(Mutex);
        sem_post(Full);
        location  = (location+1) % BUFFER_SIZE;
    }
    return 0;    
}
