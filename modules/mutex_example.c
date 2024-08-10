#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/printk.h>

static DEFINE_MUTEX(mymutex);

static int __init mutex_example_init(void)
{
    int ret;
    pr_info();
    
    ret = mutex_trylock(&mymutex);
    if(ret != 0)
    {
    	pr_info("Mutex is locked %s\n",__FUNCTION__);
    	
    	if(mutex_is_locked(&mymutex) == 0)
    	  pr_info("The mutex failed to lock!.\n");
    	  
    	mutex_unlock(&mymutex);
    	pr_info("mutex is unlocked\n");
    }else{
    	pr_info("Failed to lock\n");
    }
    return 0;    
}

static void __exit mutex_example_exit(void)
{
    pr_info("Example mutex exit\n");
}

module_init(mutex_example_init);
module_exit(mutex_example_exit);

MODULE_DESCRIPTION("Mutex example");
MODULE_LICENSE("GPL");
