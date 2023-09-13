// Required header files for kernel module development.
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/delay.h>

// Declaration of module parameters with default values.
int base_minor = 0;  // Starting minor number for device
char *device_name = "mychardev";  // Name of the device
int count = 1;  // Number of device numbers needed
dev_t devicenumber;  // Holds the device number (major and minor)

// Macro to allow the module parameters to be passed at load time.
module_param(base_minor, int, 0);
module_param(count, int, 0);
module_param(device_name, charp, 0);

// Specifies the license type for the module.
MODULE_LICENSE("GPL");

// Initialization function for the module.
static int test_hello_init(void)
{
	int i = 0;

	// Print the passed module parameters.
	printk("Minor Number :%d\n", base_minor);
	printk("Count:%d\n", count);
	printk("Device Name:%s\n", device_name);

	// Loop to try registering the device 512 times.
	for (i = 0; i < 512; i++) {
		// Attempt to allocate a character device region.
		if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
			printk("Device number registered\n");
			printk("Major number received:%d\n", MAJOR(devicenumber));
		}
		else
			printk("Device number registration Failed\n");
		
		// Introduce a delay of 1 second between each registration attempt.
		msleep(1000);
	}

	return 0;
}

// Cleanup function for the module.
static void test_hello_exit(void)
{
	// Unregister the character device region when module is removed.
	unregister_chrdev_region(devicenumber, count);
}

// Macros to specify the initialization and cleanup functions.
module_init(test_hello_init);
module_exit(test_hello_exit);
