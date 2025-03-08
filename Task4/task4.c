#include <linux/module.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladyslav Andrishko v.andrishko.v333@gmail.com");
MODULE_DESCRIPTION("Minor Major NUMBER for devices");

static int my_init_module(void);
static void my_cleanup_module(void);

static dev_t my_dev;

static int __init my_init_module(void){

	if(alloc_chrdev_region(&my_dev, 0, 1, "device_rcar") != 0){
		pr_err("Error in alloc_chrdev_region");
		return -1;
	}
	pr_info("Device alloc_chrdev_region with Major %d and Minor %d numbers\n", 
			MAJOR(my_dev), MINOR(my_dev));
	return (0);
}

static void __exit my_cleanup_module(void){
	unregister_chrdev_region(my_dev, 1);
	pr_info("Device unregister_chrdev_region\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);
