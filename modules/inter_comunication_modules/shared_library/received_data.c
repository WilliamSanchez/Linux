#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/printk.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/wait.h>

#include "shared_header.h"

struct mutex etx_mutex;
uint32_t read_count = 0;
wait_queue_head_t wait_queue_etx;
int wait_queue_flag = 0;
extern struct shared_data *data_to_send;
extern int send_data;
static struct task_struct *thread2;
static int wait_function(void *unused);
static int wait_function(void *unused)
{
    while(1)
    {
        wait_queue_flag = send_data;
        pr_info("[%s:%d] Waiting for event ..!\n", __FUNCTION__, __LINE__);
        wait_event_interruptible(wait_queue_etx, wait_queue_flag != 0);
        if(wait_queue_flag == 2)
        {   
            pr_info("[%s:%d] Event come from exit function ..!\n", __FUNCTION__, __LINE__);
            return 0;
        }
        pr_info("[%s:%d] receivde data  from send data module ..!\n", __FUNCTION__, __LINE__);
        pr_info("[%s:%d] DATA = [ %s ] len = %d..!\n", __FUNCTION__, __LINE__, (char*)data_to_send->data,data_to_send->len);
        wait_queue_flag = 0;
    }
    return 0;
}

static int __init mutex_example_init(void)
{

    pr_info("\tReceived data INIT\n");

    init_waitqueue_head(&wait_queue_etx);
    
    /*Create thread 2*/
    thread2 = kthread_run(wait_function,NULL,"etx_thread2");
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
    wait_queue_flag = 2;
    wake_up_interruptible(&wait_queue_etx);
    kthread_stop(thread2);
    pr_info("receive data module remove\n");
}

module_init(mutex_example_init);
module_exit(mutex_example_exit);

MODULE_DESCRIPTION("Mutex example");
MODULE_LICENSE("GPL");
