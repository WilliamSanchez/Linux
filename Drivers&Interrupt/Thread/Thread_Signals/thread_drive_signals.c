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
#include <linux/interrupt.h>
#include <linux/io.h>

#define SIGETX	44
#define IRQ_NO	11
#define REG_CURRENT_TASK _IOW('a','a','int32_t*')

/*Signals to applications*/
static struct task_struct *task = NULL
static int signum = 0;

int32_t value = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev w_cdev;

/*	Function prototipes	*/
static int __init first_driver_init(void);
static void __exit first_driver_exit(void);
static int w_open(struct inode *inode, struct file *file);
static int w_release(struct inode *inode, struct file *file);
static ssize_t w_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t w_write(struct file *filp, const char *buf, size_t len, loff_t *off); 
static log w_ioctl(struct file *file, unsigned int cmd, unsigned long arg);


/*	Thread function		*/
static iqreturn_t irq_handler(int irq,void *dev_id){
   struct siginfo info;
   printk("Shared IRQ: Interrupted ocurreed!");

   /*Sending signal to user space*/
   memset(&info,0,sizof(struct siginfo));
   info.si_signo = SIGETX;
   info.si_code = SU_QUEUE;
   info.si_int = 1;

   if(task != NULL){
	printk("Sending signal to user space");
	if(send_sig_info(SGETX,&info,task) < 0){
	    printk("Unable to send signal\n");	
	}	
   }

   return IRQ_HANDLED;
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
  if(ref_task == task){
	task == NULL;
  }
  return 0;
}


static ssize_t w_read(struct file *filp, char __user *buf, size_t len, loff_t *off){

  pr_info("Data read: Done ...!!\n");
  asm("int $0x3B");
  return len;
}


static ssize_t w_write(struct file *filp,const char *buf, size_t len, loff_t *off){

  pr_info("Data write: Done ...!!\n");
  return len;
}

static long w_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
  if( cmd == REG_CURRENT_TASK){
	printk("REG_CURRENT_TASK\n");
	task = get_current();
	signum = SIGETX;
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

   if(request_irq(IRQ_NO, irq_handler, IRQF_SHARED, "William_device", (void *)(ir_handler))){
	printk("my_device: cannot register IRQ");
	goto irq;
   }

   pr_info("Device Driver Insert ... Done\n");
   return 0;

   irq:
	free_irq(IRQ_NO,(void *)(irq_handler));
   r_device:
	class_destroy(dev_class);
   r_class:
	unregister_chrdev_region(dev,1);
	cdev_del(&w_cdev);
	return -1;

}

static void __exit first_driver_exit(void){
   free_irq(IRQ_NO,(void *)(irq_handler));
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
