#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Uygar Kaya");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("CS350 - Homework1 - My First Linux Driver");

static int __init hello_init(void) {
    printk(KERN_ALERT "Hello World!\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_ALERT "Goodbye, Cruel World\n");
}

module_init(hello_init);
module_exit(hello_exit);