#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/printk.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/slab.h>

#include "shared_header.h"

struct mutex etx_mutex;
unsigned long etx_globlal_variable = 0;
static struct task_struct *thread2;
int send_data = 0;
char buffer[1024] = "Data from device driver 1";
struct shared_data *data_to_send;

int thread_function2(void *pv);
int thread_function2(void *pv)
{
    while(!kthread_should_stop())
    {
        mutex_lock(&etx_mutex);
        send_data = 1;
        etx_globlal_variable++;
        data_to_send->data = kzalloc(1024,GFP_KERNEL);
        memcpy(data_to_send->data,buffer,strlen(buffer));
        data_to_send->len = strlen(buffer);
        pr_info("[%s:%d] In driver function Thread function2[%lu]\n", __FUNCTION__, __LINE__ ,etx_globlal_variable);
        mutex_unlock(&etx_mutex);
        msleep(1000);
    }
    return 0;
}

EXPORT_SYMBOL(send_data);
EXPORT_SYMBOL(data_to_send);
static int __init mutex_example_init(void)
{

    pr_info("\tSend data INIT\n");
    
    data_to_send = kzalloc(sizeof(*data_to_send), GFP_KERNEL);
    if(!data_to_send){
        pr_err("[%s:%d] Not allocation memory ..!\n", __FUNCTION__, __LINE__);
        return -1;
    }

    /*Create thread 2*/
    thread2 = kthread_run(thread_function2,NULL,"etx_thread2");
    if(thread2)
    {
        pr_err("[%s:%d] Thread created successfully ..!\n", __FUNCTION__, __LINE__);
    }else{
         pr_err("[%s:%d] Thread not created..!\n", __FUNCTION__, __LINE__);
    }

     pr_info("[%s:%d] Device Driver insert ..Done\n", __FUNCTION__, __LINE__);
     return 0;   
}

static void __exit mutex_example_exit(void)
{
     kthread_stop(thread2);
    pr_info("Example mutex exit\n");
}

module_init(mutex_example_init);
module_exit(mutex_example_exit);

MODULE_DESCRIPTION("Mutex example");
MODULE_LICENSE("GPL");
