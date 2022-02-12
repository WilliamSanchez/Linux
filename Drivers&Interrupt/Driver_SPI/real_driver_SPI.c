#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>

#define SPI_BUS_NUM	(	0)

static struct spi_device *W_spi_device;

/*Register information about your slave device*/
struct spi_board_info W_spi_device_info = {

  .modalias		= "W_spi-LSM9DS1-driver",
  .max_speed_hz		= 4000000,			// speed your device
  .bus_num		= SPI_BUS_NUM,
  .chip_select		= 0,				// Chip select
  .mode			= SPI_MODE_0			// SPI mode 0
};

/*Write SPI*/

static int W_spi_write(char data, char rcv){

  int ret = -1;
  char rx = 0x00;
  
  if(W_spi_device){
	struct spi_transfer tr = {
	   .tx_buf = &data,
	   .rx_buf = &rx,
	   .len    = 1,
	};
        spi_sync_transfer(W_spi_device,&tr,1);
	rcv = rx;
  }

  return (ret);
}


/************************************************************/

//dev_t dev = 0;
//static struct class *dev_class;
//static struct cdev w_cdev;

/*	Function prototipes	*/
/*
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
  
  //Reading GPIO state
  gpio_state = gpio_get_value(GPIO_60);

  //write to user
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
  pr_info("Write function: GPIO 60 = %d\n",rec_buf[0]);

  if(rec_buf[0] == '1'){
     gpio_set_value(GPIO_60,1);
  }else if(rec_buf[0] == '0'){
     gpio_set_value(GPIO_60,0);
  }else{
     pr_err("unknown command: please provider either 0 or 1\n");
  }

  return len;
}
*/
static int __init first_driver_init(void){
  
   int ret;
   struct spi_master *master;

   master = spi_busnum_to_master(W_spi_device_info.bus_num);
   if(master == NULL){
      pr_err("SPI Master not found.\n");
      return -ENODEV;  
   }
   
   W_spi_device = spi_new_device(master,&W_spi_device_info);
   if(W_spi_device == NULL){
      pr_err("Failed to create the slave.\n");
      return -ENODEV;
   }  

   W_spi_device->bits_per_word = 8;

   ret = spi_setup(W_spi_device);
   if(ret){
      pr_err("Failed to setup slave.\n");
      spi_unregister_device(W_spi_device);
      return -ENODEV;
   }
 
   pr_info("Driver Added!!\n");
   return ret;
}

static void __exit first_driver_exit(void){

   spi_unregister_device(W_spi_device);
   pr_info("Driver removed successfully ...\n");
}

module_init(first_driver_init);
module_exit(first_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Sanchez");
MODULE_DESCRIPTION("A simple device driver");
MODULE_VERSION("1:1.0");
