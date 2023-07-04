#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>		//kmalloc()
#include <linux/uaccess.h>	// copy_to/from_user()
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/mutex.h>


struct mutex W_mutex;
unsigned long W_global_variable = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev w_cdev;

static struct task_struct *W_thread1;
static struct task_struct *W_thread2;

int thread_function1(void *pv);
int thread_function2(void *pv);

/*	Function prototipes	*/
static int __init first_driver_init(void);
static void __exit first_driver_exit(void);
static int w_open(struct inode *inode, struct file *file);
static int w_release(struct inode *inode, struct file *file);
static ssize_t w_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t w_write(struct file *filp, const char *buf, size_t len, loff_t *off); 


/*	Thread function		*/
int thread_function1(void *pv){
 
   while(!kthread_should_stop()){
	W_global_variable++;
	mutex_lock(&W_mutex);
	pr_info("William thread function [1]... %lu\n",W_global_variable);
	mutex_unlock(&W_mutex);
	msleep(1000);
   }
   return 0;
}

int thread_function2(void *pv){
 
   while(!kthread_should_stop()){
	mutex_lock(&W_mutex);
	W_global_variable++;
	pr_info("William thread function [2]... %lu\n",W_global_variable);
	mutex_unlock(&W_mutex);
	msleep(1000);
   }
   return 0;
}



struct file_operations fops = {
  .owner	= THIS_MODULE,
  .read 	= w_read,
  .write	= w_write,
  .open		= w_open,
  .release	= w_release,
};

static int w_open(struct inode *inode, struct file *file){
  
  pr_info("Device file Opened ...!!\n");
  return 0;
}


static int w_release(struct inode *inode, struct file *file){
  pr_info("Device file closed ...!!\n");
  return 0;
}


static ssize_t w_read(struct file *filp, char __user *buf, size_t len, loff_t *off){

  pr_info("Data read: Done ...!!\n");
  return len;
}


static ssize_t w_write(struct file *filp,const char *buf, size_t len, loff_t *off){

  pr_info("Data write: Done ...!!\n");
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
 
   /*Adding character device to the system*/
   if((dev_class = class_create(THIS_MODULE,"William_class")) == NULL){
	pr_err("cannot add the deviceto the system\n");
 	goto r_class;
   }
 
   /*create device*/
   if((device_create(dev_class,NULL,dev,NULL,"William_device"))==NULL){
	pr_err("Cannot create the device\n");
	goto r_device;
   }

    /* 	Other method to create and run thread 		*/
    W_thread1 = kthread_run(thread_function1,NULL,"W thread [1]");
    if(W_thread1){
 	pr_info("Kthread1 created succesfully");
    }else{
	pr_err("Cannot create kthread\n");
	goto r_device;
    }

    /* 	Other method to create and run thread 		*/
    W_thread2 = kthread_run(thread_function2,NULL,"W thread [2]");
    if(W_thread2){
 	pr_info("Kthread2 created succesfully");
    }else{
	pr_err("Cannot create kthread\n");
	goto r_device;
    }


   pr_info("Device Driver Insert ... Done\n");
   return 0;

   r_device:
	class_destroy(dev_class);
   r_class:
	unregister_chrdev_region(dev,1);
	cdev_del(&w_cdev);
	return -1;

}

static void __exit first_driver_exit(void){
   kthread_stop(W_thread1);
   kthread_stop(W_thread2);
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
