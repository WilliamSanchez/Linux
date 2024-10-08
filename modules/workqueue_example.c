/*
			SHEDULING TASK
	
	Workqueue
	Work queues are more complicated but also better suited to running multiple things in a 
	sequence.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>

static struct workqueue_struct *queue = NULL;

static struct work_struct work;
 
 static void work_handler(struct work_struct *data)
 {
     pr_info("Work handler function\n");
 }
 
 static int __init sched_init(void)
 {
     queue = alloc_workqueue("HELLOWROLD",WQ_UNBOUND,1);
     INIT_WORK(&work,work_handler);
     queue_work(queue, &work);
     return 0;
 }
 
 static void __exit sched_exit(void)
 {
     destroy_workqueue(queue);
 }
 
 
 module_init(sched_init);
 module_exit(sched_exit);
 
 MODULE_LICENSE("GPL");
 MODULE_DESCRIPTION("Exmaple workqueue");
