#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int valueETX, arr_valueETX[4];
char *nameETX;
int cb_valueETX = 0;

module_param(valueETX,int,S_IRUSR|S_IWUSR);
module_param(nameETX,charp,S_IRUSR|S_IWUSR);
module_param_array(arr_valueETX,int,NULL,S_IRUSR|S_IWUSR);

int notify_param(const char *val, const struct kernel_param *kp){
  
  int res  = param_set_int(val,kp);
   if(res == 0){
         printk("call back function called...\n");
	 printk("New Value of cb_valueETX = %d", cb_valueETX);
         return 0;
   }
   return -1;
}

const struct kernel_param_ops my_param_ops = {
  .set = &notify_param,
  .get = &param_get_int,
};

module_param_cb(cb_valueETX,&my_param_ops,&cb_valueETX, S_IRUGO|S_IWUSR);

static int __init driver_v1_init(void){
   int i=0;
   printk("ValueETX = %d\n",valueETX);
   printk("cb_valueETX = %d\n",cb_valueETX);
   printk("nameETX = %s\n",nameETX);
   for(i=0; i<4;i++){
         printk("Arr_value[%d] =  %d\n",i,arr_valueETX[i]);
   }
   printk("kernel module inserted Succesfully....\n");
   return 0;
}

static void __exit driver_v1_exit(void){
   printk("Kernel module removed successfully");
}

module_init(driver_v1_init);
module_exit(driver_v1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Sanchez");
MODULE_DESCRIPTION("A simple module to implementer a driver");
MODULE_VERSION("1:1.0");
