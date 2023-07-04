#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>

#define I2C_BUS_AVAILABLE	(	2)
#define SLAVE_DEVICE_NAME	( "W_IMU")
#define LSM9DS1_SLAVE_ADDR_ACC	(    0x6B)	//Accel and Gyro I2C
#define LSM9DS1_SLAVE_ADDR_MGH	(    0x1E)	//Accel and Gyro I2C

static struct i2c_adapter *W_i2c_adapter = NULL;
static struct i2c_client *W_i2c_client_LSM9DS1 = NULL;

static int i2c_write(unsigned char *buf, unsigned int len){
/*
 	Sending Start condition, slave address with R/W bit
	ACK/NCK and stop conditions will be handled internally
*/
  int ret = i2c_master_send(W_i2c_client_LSM9DS1,buf,len);
  return ret;
}

/*
  out_buf 	-> buffer wherer the data to be copied 
  len		-> length of the data to read
*/

static int i2c_read(unsigned char *out_buf, unsigned int len){
  
  int ret = i2c_master_recv(W_i2c_client_LSM9DS1,out_buf,len);
  return ret;
}

/*
static void LSM9DS1_Write(bool, unsigned int len){
   
  unsigned char buf[2] = {0};
  int ret; 

  if()

}

*/

/**********************************************************
*
*
*		Structure I2C
*
*
************************************************************/

/*function probe*/
static int W_LSM9DS1_probe(struct i2c_client *client, const struct i2c_device_id *id){

//static int i2c_read(unsigned char *out_buf, unsigned int len)
  char buff[2];
   char dir[2] = {0x0F,0x0F};
  i2c_write(dir, 1);
  i2c_read(buff,1);
  pr_info("LSM9DS1 probe!!! 0x%x\n",buff[0]);
  return 0;
}

/*function remove*/
static int W_LSM9DS1_remove(struct i2c_client *client){

  pr_info("LSM9DS1 remove!!!\n");
  return 0;
}

/*slave device id*/
static struct i2c_device_id W_LSM9DS1_id[]={
	{SLAVE_DEVICE_NAME,0},
	{}
};
MODULE_DEVICE_TABLE(12c, W_LSM9DS1_id);

/*I2C driver structure*/
static struct i2c_driver W_LSM9DS1_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE,	
	},
    	.probe		= W_LSM9DS1_probe,
	.remove		= W_LSM9DS1_remove,
	.id_table	= W_LSM9DS1_id,
};

/*I2C Board info structure*/
static struct i2c_board_info LSM9DS1_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME,LSM9DS1_SLAVE_ADDR_ACC)
};

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
  
   int ret = -1;
   W_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);
  
   if(W_i2c_adapter != NULL){
 	W_i2c_client_LSM9DS1 = i2c_new_device(W_i2c_adapter,&LSM9DS1_i2c_board_info);
	if(W_i2c_client_LSM9DS1 != NULL){
	      i2c_add_driver(&W_LSM9DS1_driver);
	      ret = 0;	
	}
	i2c_put_adapter(W_i2c_adapter);
   }

   pr_info("Driver Added!!\n");
   return ret;
}

static void __exit first_driver_exit(void){

   i2c_unregister_device(W_i2c_client_LSM9DS1);
   i2c_del_driver(&W_LSM9DS1_driver);
   pr_info("Driver removed successfully ...\n");
}

module_init(first_driver_init);
module_exit(first_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Sanchez");
MODULE_DESCRIPTION("A simple device driver");
MODULE_VERSION("1:1.0");
