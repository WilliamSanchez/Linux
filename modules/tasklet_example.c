/*
			SHEDULING TASK
			
	Tasklets
	Tasklets are a quick and easy way to scheduling a single functionto be run.
	For example, when trigged from an interrumpt.  
*/

#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/printk.h>

#ifndef DECLARE_TASKLET_OLD
#define DECLARE_TASKLET_OLD(arg1,arg2) DECLARE_TASKLET(arg1,arg2,OL)
#endif

static void tasklet_fn(unsigned long data)
{
    pr_info("Example tasklet starts\n");
    mdelay(5000);
    pr_info("Example tasklet ends\n");
}

static DECLARE_TASKLET_OLD(mytask,tasklet_fn);

static int __init example_tasklet_init(void)
{
   pr_info("Tasklet example init\n");
   tasklet_schedule(&mytask);
   mdelay(2000);
   pr_info("Example tasklet init continues ...\n");
   return 0;   
}

static void __exit example_tasklet_exit(void)
{
    pr_info("Tasklet exmaple exit\n");
    tasklet_kill(&mytask);
}

module_init(example_tasklet_init);
module_exit(example_tasklet_exit);

MODULE_DESCRIPTION("tasklet example");
MODULE_LICENSE("'GPL");
