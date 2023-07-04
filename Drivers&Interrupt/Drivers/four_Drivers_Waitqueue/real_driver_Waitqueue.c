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
#include <linux/wait.h>

//#define Statically

uint32_t read_count = 0;
static struct task_struct *wait_thread;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev w_cdev;

#ifdef Statically
DECLARE_WAIT_QUEUE_HEAD(wait_queue_W);
#else
wait_queue_head_t wait_queue_W;
#endif
int wait_queue_flag = 0;

/*	Function prototipes	*/
static int __init first_driver_init(void);
static void __exit first_driver_exit(void);
static int w_open(struct inode *inode, struct file *file);
static int w_release(struct inode *inode, struct file *file);
static ssize_t w_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t w_write(struct file *filp, const char *buf, size_t len, loff_t *off); 

static struct file_operations fops = {
  .owner		= THIS_MODULE,
  .read 		= w_read,
  .write		= w_write,
  .open			= w_open,
  .release		= w_release,
};

static int wait_function(void *unused){

  while(1){
     pr_info("Waiting for event ...\n");
     wait_event_interruptible(wait_queue_W, wait_queue_flag != 0);
     if(wait_queue_flag == 2){
	pr_info("Event came from exit funcitons\n");
	return 0;
     }
     pr_info("Event Came From read Function - %d\n", ++read_count);
     wait_queue_flag = 0;
  }
  #ifdef Statically
     do_exit(0);
  #endif
  return 0;
}

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
  wait_queue_flag = 1;
  wake_up_interruptible(&wait_queue_W);
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

#ifdef Statically
   w_cdev.owner = THIS_MODULE;
   w_cdev.ops = &fops;
#endif

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

#ifndef Statically
  init_waitqueue_head(&wait_queue_W);
#endif

   /*Create device*/
   wait_thread = kthread_create(wait_function,NULL,"WaitThread");
   if(wait_thread){
        pr_info("Thread created succesfully");
	wake_up_process(wait_thread);	
   }else{
 	pr_info("Thread created failed ..\n");
   }

   pr_info("Device Driver Insert ... Done\n");
   return 0;

   r_device:
	class_destroy(dev_class);
   r_class:
	unregister_chrdev_region(dev,1);
	return -1;

}

static void __exit first_driver_exit(void){
   wait_queue_flag = 2;
   wake_up_interruptible(&wait_queue_W);
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
