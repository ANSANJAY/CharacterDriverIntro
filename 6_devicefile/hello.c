#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/device.h>


MODULE_LICENSE("GPL");
static struct class *class;

static int test_hello_init(void)
{

    class = class_create(THIS_MODULE, "myclass");


    return 0;
}

static void test_hello_exit(void)
{
	class_destroy(class);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
