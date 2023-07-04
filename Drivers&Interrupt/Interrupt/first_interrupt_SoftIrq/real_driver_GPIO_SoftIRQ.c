#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>		
#include <linux/uaccess.h>	// copy_to/from_user()
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define EN_DEBOUNCE

#ifdef EN_DEBOUNCE

#include <linux/jiffies.h>
extern unsigned long volatile jiffies;
unsigned long old_jiffie = 0;
#endif

#define GPIO_60_OUT		(60)
#define GPIO_67_IN		(67)

unsigned int led_toggle = 0;
unsigned int GPIO_irqNumber;

static irqreturn_t gpio_irq_handler(int irq, void *dev_id){

   #ifdef EN_DEBOUNCE
	unsigned long diff = jiffies - old_jiffie;
   	if(diff < 20){
	   return IRQ_HANDLED;
 	}
	old_jiffie = jiffies;
   #endif
/*   
   local_irq_save(flags);
   led_toggle=(0x01^led_toggle);
   gpio_set_value(GPIO_60_OUT,led_toggle);
   pr_info("Interrupt Ocurred: GPIO_60_OUT: %d",gpio_get_value(GPIO_60_OUT));
   local_irq_restore(flags);
*/
   raise_softirq(WSF_SOFT_IRQ);
   return IRQ_HANDLED;
}

static void gpio_interrupt_softirq_handler(struct softirq_action *action){
   led_toggle=(0x01^led_toggle);
   gpio_set_value(GPIO_60_OUT,led_toggle);
   pr_info("Interrupt Ocurred: GPIO_60_OUT: %d",gpio_get_value(GPIO_60_OUT));
}

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

  uint8_t gpio_state = 0;
  
  /*Reading GPIO state*/
  gpio_state = gpio_get_value(GPIO_60_OUT);

  /*write to user*/
  len = 1;
  if(copy_to_user(buf,&gpio_state,len) > 0){
     pr_err("ERROR: Not all the bytes have been copied to user!\n");
  }

  pr_info("Read function: GPIO 60 = %d\n",gpio_state);
  return 0;
}


static ssize_t w_write(struct file *filp,const char *buf, size_t len, loff_t *off){

  uint8_t rec_buf[10]={0};

  if(copy_from_user(rec_buf,buf,len) > 0){
	pr_info("ERROR: Not all the bytes have been copied from user\n");
  }
  pr_info("Write function: GPIO 60 set = %c\n",rec_buf[0]);

  if(rec_buf[0] == '1'){
     gpio_set_value(GPIO_60_OUT,1);
  }else if(rec_buf[0] == '0'){
     gpio_set_value(GPIO_60_OUT,0);
  }else{
     pr_err("unknown command: please provider either 0 or 1\n");
  }

  return len;
}

static int __init first_driver_init(void){

  if((alloc_chrdev_region(&dev,0,1,"WilliamSanchez_Dinamic")) <0 ){
      pr_err("cannot allocate major number for device 1\n");
      goto r_unreg;
      return -1;
   }

   pr_info("Major=%d, Minor=%d\n",MAJOR(dev),MINOR(dev));

   /*Create cdev structure*/
   cdev_init(&w_cdev,&fops);

   /*Crate struct class*/
   if((cdev_add(&w_cdev,dev,1)) < 0){
	pr_err("cannot create the struct class for device\n");
 	goto r_del;
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


   /*Cheking the gpio is valid or not*/
   if(gpio_is_valid(GPIO_60_OUT) == false){
	pr_err("Error: GPIO %d is not valid\n",GPIO_60_OUT);
 	goto r_device;
   }

   /*Resquesting the GPIO*/
   if(gpio_request(GPIO_60_OUT,"GPIO_60") < 0){
	pr_err("Error: GPIO %d request\n",GPIO_60_OUT);
 	goto r_gpio;
   }

   gpio_direction_output(GPIO_60_OUT,0);

   /*Cheking the gpio is valid or not*/
   if(gpio_is_valid(GPIO_67_IN) == false){
	pr_err("Error: GPIO %d is not valid\n",GPIO_67_IN);
 	goto r_device;
   }

   /*Resquesting the GPIO*/
   if(gpio_request(GPIO_67_IN,"GPIO_67") < 0){
	pr_err("Error: GPIO %d request\n",GPIO_67_IN);
 	goto r_gpio;
   }

   gpio_direction_input(GPIO_67_IN);

   #ifndef EN_DEBOUNCE
   if(gpio_set_debounce(GPIO_67_IN,200) < 0){
	pr_err("ERROR: gpio_set_debounce -%d\n",GPIO_67_IN);
   }
   #endif

   GPIO_irqNumber = gpio_to_irq(GPIO_67_IN);
   pr_info("GPIO_irqNumber = %d\n",GPIO_irqNumber);

   if(request_irq(GPIO_irqNumber,(void*)gpio_irq_handler,IRQF_TRIGGER_RISING,"William_device",NULL)){
	pr_err("My device cannot register IRQ\n");
	goto r_gpio_in;
   }

   /*Assign gpio_interrupt_softirq_handler to the WSF*/
   open_softirq(WSF_SOFT_IRQ,gpio_interrupt_softirq_handler);

   pr_info("Device Driver Insert ... Done\n");
   return 0;

   r_gpio_in:
	gpio_free(GPIO_67_IN);
   r_gpio:
	gpio_free(GPIO_60_OUT);
   r_device:
	device_destroy(dev_class,dev);
   r_class:
	class_destroy(dev_class);
   r_del:
      	cdev_del(&w_cdev);
   r_unreg:
	unregister_chrdev_region(dev,1);

   return -1;
}

static void __exit first_driver_exit(void){
   free_irq(GPIO_irqNumber,NULL);
   gpio_free(GPIO_67_IN);
   gpio_free(GPIO_60_OUT);
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
