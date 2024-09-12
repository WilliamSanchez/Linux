/*
	Spinlocks lock up the CPU that the code is running on,
	taking 100% of its resources.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/spinlock.h>

static DEFINE_SPINLOCK(sl_static);
static spinlock_t sl_dynamic;

static void example_spinlock_static(void)
{
   unsigned long flags;
   
   spin_lock_irqsave(&sl_static,flags);
   pr_info("Locked static spinlock [%s]\n",__FUNCTION__);

     /*
         Do something or other safely. Because this  use 100% time,
         this code shouldtake no more than a few milliseconds to run.
     */

   spin_unlock_irqrestore(&sl_static, flags);
   pr_info("Unlocked static spinlock\n");

}

static void example_spinlock_dynamic(void)
{
     unsigned long flags;
     spin_lock_init(&sl_dynamic);
     spin_lock_irqsave(&sl_dynamic, flags);
     pr_info("Locked dyanmic spinlock\n");
     
     /*
         Do something or other safely. Because this  use 100% time,
         this code shouldtake no more than a few milliseconds to run.
     */
     
     spin_unlock_irqrestore(&sl_dynamic,flags);
     pr_info("Unlocked dynamic spinlock\n");
}

static int __init example_spinlock_init(void)
{
    pr_info("example spinlock started\n");
    
    example_spinlock_static();
    example_spinlock_dynamic();
    
    return 0;
}

static void __exit example_spinlock_exit(void)
{
    pr_info("Exmaple spinlock exit\n");
}

module_init(example_spinlock_init);
module_exit(example_spinlock_exit);

MODULE_DESCRIPTION("Spinlock example");
MODULE_LICENSE("GPL");
