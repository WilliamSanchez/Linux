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


struct mutex etx_mutex;
unsigned long etx_globlal_variable = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

static struct task_struct *thread1;
static struct task_struct *thread2;

static int driver_open(struct inode *inode, struct file *file);
static int driver_release(struct inode *inode, struct file *file);
static ssize_t driver_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t driver_write(struct file *filp, const char  *buf, size_t len, loff_t *off);

int thread_function1(void *pv);
int thread_function2(void *pv);

int thread_function1(void *pv)
{
    while(!kthread_should_stop())
    {
        mutex_lock(&etx_mutex);
        etx_globlal_variable++;
        pr_info("[%s:%d] In driver function Thread function1[%lu]\n", __FUNCTION__, __LINE__, etx_globlal_variable);
        mutex_unlock(&etx_mutex);
        msleep(1000);
    }
    return 0;
}

int thread_function2(void *pv)
{
    while(!kthread_should_stop())
    {
        mutex_lock(&etx_mutex);
        etx_globlal_variable++;
        pr_info("[%s:%d] In driver function Thread function2[%lu]\n", __FUNCTION__, __LINE__ ,etx_globlal_variable);
        mutex_unlock(&etx_mutex);
        msleep(1000);
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

    /*Create thread 1*/
    thread1 = kthread_run(thread_function1,NULL,"etx_thread1");
    if(thread1)
    {
        pr_err("[%s:%d] Treadh 1 created successfully ..!\n", __FUNCTION__, __LINE__);
    }else{
         pr_err("[%s:%d] Treadh 1 not created..!\n", __FUNCTION__, __LINE__);
         goto r_device;
    }

    /*Create thread 2*/
    thread2 = kthread_run(thread_function2,NULL,"etx_thread2");
    if(thread2)
    {
        pr_err("[%s:%d] Treadh 2 created successfully ..!\n", __FUNCTION__, __LINE__);
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
    kthread_stop(thread1);  
    kthread_stop(thread2);
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