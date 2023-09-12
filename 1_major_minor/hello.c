// Including necessary headers for the kernel module
#include <linux/kernel.h>       // Kernel core header with core types and macros
#include <linux/module.h>       // Core headers for loading LKMs (Linux Kernel Modules) into the kernel
#include <linux/kdev_t.h>       // Provides device type macros and functions

// Specifies the module's license as GPL
MODULE_LICENSE("GPL");

// Initialization function executed when the module is loaded
static int test_hello_init(void)
{
    dev_t devicenumber; // Declares a device type variable

    // Print uninitialized device numbers
    printk("Major Number :%d\n", MAJOR(devicenumber));
    printk("Minor Number :%d\n", MINOR(devicenumber));

    // Manually set devicenumber to 49 and then print its major and minor parts
    devicenumber = 49;
    printk("Major Number :%d\n", MAJOR(devicenumber));
    printk("Minor Number :%d\n", MINOR(devicenumber));

    // Use the MKDEV macro to set major and minor numbers, then print them
    devicenumber = MKDEV(120, 30);
    printk("Major Number :%d\n", MAJOR(devicenumber));
    printk("Minor Number :%d\n", MINOR(devicenumber));

    return 0; // Return 0 to indicate successful initialization
}

// Cleanup function executed when the module is unloaded
static void test_hello_exit(void)
{
    // No cleanup tasks are present in this module
}

// Specifies the initialization and cleanup functions for the module
module_init(test_hello_init);
module_exit(test_hello_exit);
