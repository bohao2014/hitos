#include <string.h>
#include <errno.h>
#include <asm/segment.h>

char msg[24]; //23个字符 +'\0' = 24

int sys_iam(const char* name)
{
    //printk("=========================\n");
    //printk("entering sys_iam\n");
    //printk("=========================\n");
    
    // copy input to a tmp string
    char tmp[30];
    int i;
    for(i=0; i<30; i++)
    {
        tmp[i] = get_fs_byte(name+i);
        if(tmp[i] == 0)
            break;
    }
    //printk("tmp=%s\n",tmp);

    if(i>23)
    {
        printk("string is too long, no longer than 23 char\n");
        return -(EINVAL);
    }

    //memcpy(msg, tmp, i);
    int len = i;
    strcpy(msg, tmp);
    //memcpy(msg, tmp, len);
    //for(i=0; i<10000; i++) {}
    //printk("msg=%s, len=%d, &msg=%p\n",msg,len,&msg);
    //for (i=0; i<len; i++)
    //{
    //    printk("msg[%d]=%c ", i, msg[i]);
    //    printk("\n");
    //}
    //printk("msg=%s, len=%d, &msg=%p\n",msg,len,&msg);
    //printk("leaving sys_iam\n");
    return i;
}

int sys_whoami(char* name, unsigned int size)
{
    //printk("=========================\n");
    //printk("entering sys_whoami\n");
    //printk("=========================\n");

    //printk("msg=%s\n", msg);
    int i=0;
    for(;msg[i]!=0;i++) {}
    if(i>size)
    {
        return -(EINVAL);
    }
    int len = i;
    //printk("len=%d\n", len);

    for(i=0;i<len;i++)
    {
        put_fs_byte(msg[i],name+i);
    }

    //printk("leaving sys_whoami\n");
    return i;
}
