// Include necessary headers
#include <linux/kernel.h>       // Contains types, macros, functions for the kernel
#include <linux/module.h>       // Core headers for loading LKMs into the kernel
#include <linux/kdev_t.h>       // Kernel device type macros
#include <linux/fs.h>           // File system structure definitions, functions, etc.

// Initialization of variables
int major_number = 120;        // Default major number
int minor_number = 0;          // Default minor number
char *device_name = "mychardev"; // Default device name
int count = 1;                 // Default count of devices
dev_t devicenumber;            // Will store the device number

// Allow module parameters to be passed at load time
module_param(major_number, int, 0);
module_param(minor_number, int, 0);
module_param(count, int, 0);
module_param(device_name, charp, 0);

MODULE_LICENSE("GPL");        // Define the module's license

// Initialization function
static int test_hello_init(void)
{
	// Create a device number from major and minor numbers
	devicenumber = MKDEV(major_number, minor_number);
	
	// Print device details
	printk("Major Number :%d\n", MAJOR(devicenumber));
	printk("Minor Number :%d\n", MINOR(devicenumber));
	printk("Count:%d\n", count);
	printk("Device Name:%s\n", device_name);

	// Try to register the char device region
	if (!register_chrdev_region(devicenumber, count, device_name))
		printk("Device number registered\n");
	else
		printk("Device number registration Failed\n");

	return 0;
}

// Cleanup function
static void test_hello_exit(void)
{
	// Unregister the char device region
	unregister_chrdev_region(devicenumber, count);
}

// Specify the initialization and cleanup functions
module_init(test_hello_init);
module_exit(test_hello_exit);
