#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladyslav Andrishko v.andrishko.v333@gmail.com");
MODULE_DESCRIPTION("Timer use-case example");


int status = 43;

static struct timer_list my_timer;  // Timer object


static int __init my_init_module(void);
static void __exit my_cleanup_module(void);

static int timer_set(const char *val, const struct kernel_param *kp){

	int delay = 0;
    if (kstrtoint(val, 10, &delay) != 0) {
        pr_err("Invalid value for timer delay.\n");
        return -EINVAL;
    }

	del_timer_sync(&my_timer);	
	pr_info("We start the timer\n");
	mod_timer(&my_timer, jiffies + delay * HZ);
		
	return param_set_int(val, kp);
}

static void timer_callb(struct timer_list *timer){
	pr_info("Timer ends\n");
}

static int __init my_init_module(void){
	pr_info("Timer TEST MODULE\n");

	timer_setup(&my_timer, timer_callb, 0);
	return (0);
}

static void __exit my_cleanup_module(void){
	del_timer_sync(&my_timer);
	pr_info("Good by TIMER TEST MOD\n");
}


static const struct kernel_param_ops timer_ops =	
{
	.set = &timer_set,
	.get = &param_get_int,

};
module_param_cb(status, &timer_ops, &status, 0644);

module_init(my_init_module);
module_exit(my_cleanup_module);
