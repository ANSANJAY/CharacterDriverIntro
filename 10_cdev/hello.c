// Essential Kernel Headers
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>  // For Major and Minor numbers
#include <linux/fs.h>      // File system operations
#include <linux/device.h>  // Supports Kernel Driver Model
#include <linux/cdev.h>    // Character device structures

// Device Metadata
int base_minor = 0;              // Starting minor number
char *device_name = "mychardev"; // Name of the device
int count = 1;                   // Number of minor numbers, representing devices
dev_t devicenumber;              // Will hold the major and minor number

// Device structures
static struct class *class = NULL;          // Represents a class of devices (like a category)
static struct device *device = NULL;        // Represents a single device that can be made accessible to userspace
static struct cdev *mycdev = NULL;          // Represents a character device

MODULE_LICENSE("GPL");  // Specifies license info for the module

// These functions handle operations on the device
static int device_open(struct inode *inode, struct file *file) {...}
static int device_release(struct inode *inode, struct file *file) {...}
static ssize_t device_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offset) {...}
static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *offset) {...}

// Maps user file operations (open, read, write) to driver's implementations
struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

// This function is called when the driver is loaded. Sets up device numbers and initializes the device.
static int test_hello_init(void) {...}

// This function is called when the driver is removed. Cleans up.
static void test_hello_exit(void) {...}

module_init(test_hello_init);  // Specifies the initialization function
module_exit(test_hello_exit);  // Specifies the cleanup function
