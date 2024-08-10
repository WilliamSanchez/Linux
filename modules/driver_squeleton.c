#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/fs.h>


static unsigned int major; /*major number for device*/
static struct class *squeleton_class;
static struct cdev squeleton_cdev;

int squeleton_open(struct inode *inode, struct file *filp)
{
	pr_info("Someone tried to open me\n");
	return 0;
}

int squeleton_release(struct inode *inode, struct file *filp)
{
	pr_info("someone closed me\n");
	return 0;
}

static ssize_t squeleton_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
	pr_info("Nothig to read guy\n");
	// if(copy_to_user(buff, dataTosend, count)!=0)
	//	{
	//	    retval = -EIO;
	//	    goto end_read;
	//	}
	return 0;
}

static ssize_t squeleton_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	ssize_t retval=0;
	pr_info("Can't accept any dat guy\n");
	// if(copy_from_user(buff, dataToreceive, count)!=0)
	//	{
	//	    retval = -EFAULT;
	//	    goto end_write;
	//	}
	return retval;
}

static struct file_operations squeleton_fops = {
	.open=		squeleton_open,
	.release=	squeleton_release,
	.read=		squeleton_read,
	.write=		squeleton_write,

};

static int my_pdrv_probe(struct platform_device *pdev)
{
	struct device *squeleton_device;
	int error;
	dev_t devt=0;
	
	/*Get a range of minor numbers (starting with 0) to work with*/
	error=alloc_chrdev_region(&devt,0,1,"squeleton_char");
	if(error < 0)
	{
		pr_err("Can't get major number\n");
		return error;
	}
	
	major = MAJOR(devt);
	pr_info("squeleton_char major number = %d\n", major);
	
	/* Create device class, visible in /sys/class */
	squeleton_class = class_create("squeleton_char_class");
	if(IS_ERR(squeleton_class))
	{
		pr_err("Error creating sdma test module clas.\n");
		unregister_chrdev_region(MKDEV(major,0),1);
		return PTR_ERR(squeleton_class);
	}
	
	/* Initialize the char device and tie a file_operaqtions to it */
	cdev_init(&squeleton_cdev, &squeleton_fops);
	
	squeleton_device = device_create(squeleton_class,
					 &pdev->dev, 	/* no parent device */
					 devt, 		/* associated dev_t */
					 NULL,		/* no additianl data */
					 "squeleton_char" );	/* device name */	

	if (IS_ERR(squeleton_device))
	{
		pr_err("Error creating sdma test class device.\n");
		class_destroy(squeleton_class);
		unregister_chrdev_region(devt, 1);
		return -1;
	}
	
	pr_info("squeleton char module loaded\n");
	return 0;
}


static int my_pdrv_remove(struct platform_device *pdev)
{
	unregister_chrdev_region(MKDEV(major,0),1);
	device_destroy(squeleton_class, MKDEV(major, 0));
	cdev_del(&squeleton_cdev);
	class_destroy(squeleton_class);
	
	pr_info("Squeleton char module loaded\n");
	return 0;
}

static struct platform_driver mypdrv = {
	.probe		= my_pdrv_probe,
	.remove		= my_pdrv_remove,
	.driver		= {
		.name 	  = "platform-squeleton-char",
		.owner	  = THIS_MODULE,
	},
};

module_platform_driver(mypdrv);
MODULE_AUTHOR("device dirver squeleton");
MODULE_LICENSE("GPL");
