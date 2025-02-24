#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

int my_init_module(void);
void my_cleanup_module(void);

static	int number = 0;
static	char*  word ="Hello From Kernel World!!!";

module_param(number, int, 0644);
MODULE_PARM_DESC(number, "Some integer");

module_param(word, charp, 0644);
MODULE_PARM_DESC(word, "Some string");

int my_init_module(void){
	printk(KERN_INFO "%s times : %d\n", word, number);
	return (0);
}

void my_cleanup_module(void){
	printk(KERN_INFO "Bye, Bye from Kernel World!!!\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladyslav Andrishko v.andrishko.v333@gmail.com");
MODULE_DESCRIPTION("Hello world kernel module");
