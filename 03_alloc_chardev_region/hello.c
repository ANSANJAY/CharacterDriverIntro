// Required header files for kernel module development
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

// Setting default values for parameters
int base_minor = 0;               // Default minor number
char *device_name = "mychardev";  // Default device name
int count = 1;                    // Default count of minor numbers
dev_t devicenumber;               // Device number type to store major and minor numbers

// Allow these parameters to be passed at module insertion time
module_param(base_minor, int, 0);
module_param(count, int, 0);
module_param(device_name, charp, 0);

// Set the license for this module
MODULE_LICENSE("GPL");

// Initialization function of the module
static int test_hello_init(void)
{
    // Printing the passed (or default) parameters
    printk("Minor Number :%d\n", base_minor);
    printk("Count:%d\n", count);
    printk("Device Name:%s\n", device_name);

    // Attempt to dynamically allocate a character device number
    if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
        printk("Device number registered\n");
        printk("Major number received:%d\n", MAJOR(devicenumber));
    }
    else {
        printk("Device number registration Failed\n");
    }

    return 0;
}

// Cleanup function of the module
static void test_hello_exit(void)
{
    // Unregister the device number
    unregister_chrdev_region(devicenumber, count);
}

// Macros to indicate the initialization and exit functions of this module
module_init(test_hello_init);
module_exit(test_hello_exit);
