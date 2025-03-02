#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladyslav Andrishko v.andrishko.v333@gmail.com");
MODULE_DESCRIPTION("Hello world kernel module");

int my_init_module(void);
void my_cleanup_module(void);

static	int number = 0;
static	char*  word ="Hello From Kernel World!!!";

module_param(number, int, 0644);
MODULE_PARM_DESC(number, "Some integer");

module_param(word, charp, 0644);
MODULE_PARM_DESC(word, "Some string");

int __init my_init_module(void){
	pr_info("%s times : %d\n", word, number);
	return (0);
}

void __exit my_cleanup_module(void){
	pr_info("Bye, Bye from Kernel World!!!\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);
