#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/err.h>


dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t etx_write(struct file *filp, const char *buf, size_t len, loff_t *off);
void etx_shared_func(void);

int etx_count = 0;   // export variable
void etx_shared_func(void)
{   
    printk("Shared function been called !!!\n");
    etx_count++;
}

EXPORT_SYMBOL(etx_count);
EXPORT_SYMBOL(etx_shared_func);

static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .read       = etx_read,
    .write      = etx_write,
    .open       = etx_open,
    .release    = etx_release,
};

static int etx_open(struct inode *inode, struct file *file)
{
    pr_info("Device file opened...!!!");
    return 0;
}

static int etx_release(struct inode *inode, struct file *file)
{
    pr_info("Device file closed...!!!");
    return 0;
}

static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    pr_info("Data read : Done !\n");
    return 1;
}

static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    pr_info("Data write : Done !\n");
    return len;
}

static int __init etx_driver_init()
{
    if((alloc_chrdev_region(&dev,0,1,"etx_Dev1")) < 0)
    {
        pr_err("Cannot allocate major number\n");
        return -1;
    }

    pr_info("Major = %d Minor = %d\n", MAJOR(dev), MINOR(dev));

    cdev_init(&etx_cdev, &fops);

    if((cdev_add(&etx_cdev, dev, 1)) < 0)
    {
        pr_err("Cannot add the device to the system\n");
        goto r_class;
    }

    if(IS_ERR(dev_class = class_create("etx_class_1")))
    {
        pr_err("Cannot create the struct class\n");
        goto r_class;
    }

    if(IS_ERR(device_create(dev_class, NULL, dev, NULL, "etx_device1")))
    {
        pr_err("Cannot create the device !!!\n");
        goto r_device;
    }

    pr_info("Device driver 1 Inster ..Done !!!\n");
    return 0;

    r_device:
        class_destroy(dev_class);
    
    r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

static void __exit etx_driver_exit()
{
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
    cdev_del(&etx_cdev);
    unregister_chrdev_region(dev,1);
    pr_info("Devicedriver 1 remove .. done!!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Sanchez");
MODULE_DESCRIPTION("Export symbol driver");
MODULE_VERSION("1.0");

