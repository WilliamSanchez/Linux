#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>                 //kmalloc
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/err.h>
#include <linux/wait.h>


uint32_t read_count = 0;
wait_queue_head_t wait_queue_etx;
int wait_queue_flag = 0;

struct mutex etx_mutex;
unsigned long etx_globlal_variable = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

static struct task_struct *thread1;

static int driver_open(struct inode *inode, struct file *file);
static int driver_release(struct inode *inode, struct file *file);
static ssize_t driver_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t driver_write(struct file *filp, const char  *buf, size_t len, loff_t *off);

static int wait_function(void *unused)
{
    while(1)
    {
        pr_info("[%s:%d] Waiting for event ..!\n", __FUNCTION__, __LINE__);
        wait_event_interruptible(wait_queue_etx, wait_queue_flag != 0);
        if(wait_queue_flag == 2)
        {   
            pr_info("[%s:%d] Event come from exit function ..!\n", __FUNCTION__, __LINE__);
            return 0;
        }
        pr_info("[%s:%d] Event come read function ..!\n", __FUNCTION__, __LINE__);
        wait_queue_flag = 0;
    }
    return 0;
}

static struct file_operations fops = 
{
    .owner      =   THIS_MODULE,
    .read       =   driver_read,
    .write      =   driver_write,
    .open       =   driver_open,
    .release    =   driver_release,
};


static int driver_open(struct inode *inode, struct file *file)
{
    pr_info("[%s:%d] Device file open ..!\n", __FUNCTION__, __LINE__);
    return 0;
}

static int driver_release(struct inode *inode, struct file *file)
{
    pr_info("[%s:%d] Device file close ..!\n", __FUNCTION__, __LINE__);
    return 0;    
}

static ssize_t driver_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    pr_info("[%s:%d] Device read function ..!\n", __FUNCTION__, __LINE__);
    wait_queue_flag = 1;
    wake_up_interruptible(&wait_queue_etx);
    return 0;
}

static ssize_t driver_write(struct file *filp, const char  *buf, size_t len, loff_t *off)
{
    pr_info("[%s:%d] Device write function ..!\n", __FUNCTION__, __LINE__);
    return 0;
}

static int __init etx_driver_init(void)
{
    if((alloc_chrdev_region(&dev, 0, 1, "etx_dev")) < 0)
    {
        pr_info("[%s:%d] Cannot allocate major number\n", __FUNCTION__, __LINE__);
        return -1;
    }

    pr_info("[%s:%d] Major = %d, Minor = %d", __FUNCTION__, __LINE__, MAJOR(dev),MINOR(dev));

    cdev_init(&etx_cdev,&fops);

    /*Adding character device to system*/
    if(cdev_add(&etx_cdev, dev, 1) < 0)
    {
        pr_info("[%s:%d] Cannot add the device to system\n", __FUNCTION__, __LINE__);
        goto r_class;
    }

    /*Creating struct class*/
    if(IS_ERR(dev_class = class_create("etx_class")))
    {
        pr_info("[%s:%d] Cannot create the struct class\n", __FUNCTION__, __LINE__);
        goto r_class;
    }

    /*Creating device class*/
    if(IS_ERR(device_create(dev_class, NULL, dev, NULL, "etx_device")))
    {
        pr_info("[%s:%d] Cannot create the Device\n", __FUNCTION__, __LINE__);
        goto r_device;
    }

    init_waitqueue_head(&wait_queue_etx);

    thread1 = kthread_run(wait_function,NULL,"wait_thread1");
    if(thread1)
    {
        pr_err("[%s:%d] Treadh 1 created successfully ..!\n", __FUNCTION__, __LINE__);
    }else{
         pr_err("[%s:%d] Treadh 1 not created..!\n", __FUNCTION__, __LINE__);
         goto r_device;
    }

    pr_info("[%s:%d] Device Driver insert ..Done\n", __FUNCTION__, __LINE__);
     return 0;

    r_device:
        class_destroy(dev_class);
    r_class:
        unregister_chrdev_region(dev,1);
        return -1;

}

static void __exit etx_driver_exit(void)
{
    wait_queue_flag = 2;
    wake_up_interruptible(&wait_queue_etx);
    kthread_stop(thread1);  
    class_destroy(dev_class);
    cdev_del(&etx_cdev);
    unregister_chrdev_region(dev,1);
    pr_info("[%s:%d] Device Driver remove ..Done\n", __FUNCTION__, __LINE__);
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Sanchez");
MODULE_DESCRIPTION("A simple treadh implementation - Mutex");
MODULE_VERSION("1");