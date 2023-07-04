#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>		//kmalloc()
#include <linux/uaccess.h>	// copy_to/from_user()
#include <linux/ioctl.h>
#include <linux/proc_fs.h>

#define WR_VALUE _IOW('a','b',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

#define LINUX_KERNEL_VERSION	419

int32_t value = 0;
char w_array[20]="William_proc_array\n";
static int len = 1;


dev_t dev = 0;
static struct class *dev_class;
static struct cdev w_cdev;
static struct proc_dir_entry *parent;

/*	Function prototipes	*/
static int __init first_driver_init(void);
static void __exit first_driver_exit(void);
static int w_open(struct inode *inode, struct file *file);
static int w_release(struct inode *inode, struct file *file);
static ssize_t w_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t w_write(struct file *filp, const char *buf, size_t len, loff_t *off); 
static long w_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/*	Proocfs	Functions	*/
static int p_open(struct inode *inode, struct file *file);
static int p_release(struct inode *inode, struct file *file);
static ssize_t p_read(struct file *filp, char __user *buffer, size_t length, loff_t *off);
static ssize_t p_write(struct file *filp, const char *buff, size_t len, loff_t *off);

struct file_operations fops = {
  .owner		= THIS_MODULE,
  .read 		= w_read,
  .write		= w_write,
  .open			= w_open,
  .unlocked_ioctl	= w_ioctl,
  .release		= w_release,
};

#if (LINUX_KERNEL_VERSION > 505)
  static struct file_operations proc_ops = {
	.proc_open = p_open,
	.proc_read = p_read,
	.proc_write = p_write,
	.proc_release = p_release
  }; 
#else
  static struct file_operations proc_ops = {
	.open = p_open,
	.read = p_read,
	.write = p_write,
	.release = p_release
  }; 
#endif

static int p_open(struct inode *inode, struct file *file){
  pr_info("proc failed opened ..\n");
  return 0;
}

static int p_release(struct inode *inode, struct file *file){
  pr_info("proc failed released ..\n");
  return 0;
}
static ssize_t p_read(struct file *filp, char __user *buffer, size_t length, loff_t *off){

  pr_info("Device file read ...!!\n");
  if(len){
    len = 0;
  }else{
    len = 1;
    return 0;
  }

  if(copy_to_user(buffer,w_array,20)){
    pr_err("Data send: Err!\n");
  }
  return length;
}
static ssize_t p_write(struct file *filp, const char *buff, size_t len, loff_t *off){
  pr_info("proc file wrote.... \n");
  if(copy_from_user(w_array,buff,len)){
     pr_err("Data write: Err!\n");
  }
  return len;
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

  pr_info("Data read: Done ...!!\n");
  return 0;
}


static ssize_t w_write(struct file *filp,const char *buf, size_t len, loff_t *off){

  pr_info("Data write: Done ...!!\n");
  return len;
}

static long w_ioctl(struct file *file, unsigned int cmd, unsigned long arg){

   switch(cmd){
	case WR_VALUE:
		if(copy_from_user(&value,(int32_t*)arg,sizeof(value))){
		   pr_err("Data writte : Err !\n");
		}
		pr_info("value = %d\n",value);
		break;		
	case RD_VALUE:
		if(copy_to_user((int32_t*)arg,&value,sizeof(value))){
			pr_err("Data Read: Err!\n");
		}
		break;
	default:
		pr_info("Default\n");
	  	break;
   }
   return 0;
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

   parent = proc_mkdir("W_dir",NULL);

   if(parent == NULL){
      pr_info("Error creating proc entry");
      goto r_device;
   }

   proc_create("w_proc",0666,parent,&proc_ops);
  
   pr_info("Device Driver Insert ... Done\n");
   return 0;

   r_device:
	class_destroy(dev_class);
   r_class:
	unregister_chrdev_region(dev,1);
	return -1;

}

static void __exit first_driver_exit(void){

   proc_remove(parent);

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
