#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>		//kmalloc()
#include <linux/uaccess.h>	// copy_to/from_user()
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/workqueue.h>

#define IRQ_NO	11

//#define Statically
//#define Dinamically
#define Manually

void workqueue_fn(struct work_struct *work);

#ifdef Statically
  DECLARE_WORK(workqueue,workqueue_fn);
#endif

#ifdef Dinamically
  static struct work_struct workqueue;
#endif

#ifdef Manually
  DECLARE_WORK(work,workqueue_fn);
  static struct workqueue_struct *own_workqueue;
#endif

void workqueue_fn(struct work_struct *work){
    printk("Executing workqueue function\n");
}
/*	Interrupt handler for IRQ 11	*/
static irqreturn_t irq_handler(int irq, void *dev_id){
   printk("Shared IRQ: Interrupt occurred");
#ifdef Manually
   queue_work(own_workqueue,&work);
#elif
   schedule_work(&workqueue);
#endif
   return IRQ_HANDLED;
}

volatile int W_value = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev w_cdev;
struct kobject *kobj_ref;

/*	Function prototipes	*/
static int __init first_driver_init(void);
static void __exit first_driver_exit(void);
static int w_open(struct inode *inode, struct file *file);
static int w_release(struct inode *inode, struct file *file);
static ssize_t w_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t w_write(struct file *filp, const char *buf, size_t len, loff_t *off); 

/*	SysFS functions		*/
static ssize_t s_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t s_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);
struct kobj_attribute w_attr = __ATTR(W_value, 0660,s_show,s_store);

static struct file_operations fops = {
  .owner		= THIS_MODULE,
  .read 		= w_read,
  .write		= w_write,
  .open			= w_open,
  .release		= w_release,
};

static ssize_t s_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
    pr_info("SysFS - read !!!\n");
    return sprintf(buf,"%d",W_value);
}

static ssize_t s_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count){
   pr_info("SysFS - Write !!!\n");
   sscanf(buf,"%d",&W_value);
   return count;
}
/************************************************/
/*	File operations development		*/
/******************************************s******/

static int w_open(struct inode *inode, struct file *file){
  
  pr_info("Device file Opened ...!!\n");
  return 0;
}


static int w_release(struct inode *inode, struct file *file){

  pr_info("Device file closed ...!!\n");
  return 0;
}


static ssize_t w_read(struct file *filp, char __user *buf, size_t len, loff_t *off){
  pr_info("Read function ...!!\n");
  asm("int $0x3B");		//corresponding to irq 11
  return 0;
}


static ssize_t w_write(struct file *filp,const char *buf, size_t len, loff_t *off){

  pr_info("Write functions ...!!\n");
  return len;
}

static int __init first_driver_init(void){

  if((alloc_chrdev_region(&dev,0,1,"WilliamSanchez_Dinamic")) <0 ){
      pr_err("cannot allocate major number for device 1\n");
      return -1;
   }

   pr_info("Major=%d, Minor=%d\n",MAJOR(dev),MINOR(dev));

   /*Create cdev structure*/
   cdev_init(&w_cdev,&fops);

   /*Crate struct class*/
   if((cdev_add(&w_cdev,dev,1)) < 0){
	pr_err("cannot create the struct class for device\n");
 	goto r_class;
   }
 
   /*Crate struct class*/
   if((dev_class = class_create(THIS_MODULE,"William_class")) == NULL){
	pr_err("cannot add the deviceto the system\n");
 	goto r_class;
   }
 
   /*create device*/
   if((device_create(dev_class,NULL,dev,NULL,"William_device"))==NULL){
	pr_err("Cannot create the device\n");
	goto r_device;
   }

   /*Creating a directory in /sys/kernel*/
   kobj_ref = kobject_create_and_add("W_SysFS",kernel_kobj);

   /*Creating sysfs file for W_values*/
   if(sysfs_create_file(kobj_ref,&w_attr.attr)){
        pr_err("Cannot create sysfs file.....\n");
        goto r_sysfs;
   }


   if(request_irq(IRQ_NO,irq_handler,IRQF_SHARED,"William_device",(void *)(irq_handler))){
       pr_err("my device: cannot register IRQ");
       goto irq;
   }

#ifdef Dinamically
  /*Creating work by Dynamic method*/
  INIT_WORK(&workqueue,workqueue_fn);
#endif

#ifdef Manually
  /*Creating work by Dynamic method*/
  own_workqueue=create_workqueue("own_wq");
#endif 
 

   pr_info("Device Driver Insert ... Done\n");
   return 0;

   irq:
	free_irq(IRQ_NO,(void*)(irq_handler));
   r_sysfs:
	kobject_put(kobj_ref);
        sysfs_remove_file(kernel_kobj,&w_attr.attr);
   r_device:
	class_destroy(dev_class);
   r_class:
	unregister_chrdev_region(dev,1);
        cdev_del(&w_cdev);
	return -1;
}

static void __exit first_driver_exit(void){
#ifdef Manually
  /*Creating work by Dynamic method*/
  destroy_workqueue(own_workqueue);
#endif 
   free_irq(IRQ_NO,(void*)(irq_handler));
   kobject_put(kobj_ref);
   sysfs_remove_file(kernel_kobj,&w_attr.attr);
   device_destroy(dev_class,dev);
   class_destroy(dev_class);
   cdev_del(&w_cdev);
   unregister_chrdev_region(dev,1);
   pr_info("Kernel module removed successfully ...\n");
}

module_init(first_driver_init);
module_exit(first_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Sanchez");
MODULE_DESCRIPTION("A simple device driver");
MODULE_VERSION("1:1.0");
