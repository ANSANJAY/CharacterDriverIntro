// Including necessary header files
#include <linux/kernel.h>   // Core header for the kernel
#include <linux/module.h>   // Contains structures and routines for building kernel modules
#include <linux/delay.h>    // Provides delay functions
#include <linux/device.h>   // Device & class specific functions
#include <linux/cdev.h>     // cdev structures and functions

// Every module must use the MODULE_LICENSE macro to declare the license terms
MODULE_LICENSE("GPL");

// Defining static pointers and device type (dev_t) structures
static struct class *class;
static struct device *device1, *device2;
dev_t dev1, dev2;

// Module initialization function
static int test_hello_init(void)
{
    // Creating device numbers with a specific major and minor number
    dev1 = MKDEV(200, 1);
    dev2 = MKDEV(200, 2);

    // Creating a class named "myclass"
    class = class_create(THIS_MODULE, "myclass");

    // Creating two devices under "myclass", with names "mydevice1" and "mydevice2" 
    // and associated device numbers
    device1 = device_create(class, NULL, dev1, NULL, "mydevice%d", 1);
    device2 = device_create(class, NULL, dev2, NULL, "mydevice%d", 2);

    return 0;
}

// Module exit function
static void test_hello_exit(void)
{
    // Destroying the two created devices
    device_destroy(class, dev1);
    device_destroy(class, dev2);

    // Destroying the created class
    class_destroy(class);
}

// Specifying the initialization and exit functions for the module
module_init(test_hello_init);
module_exit(test_hello_exit);
