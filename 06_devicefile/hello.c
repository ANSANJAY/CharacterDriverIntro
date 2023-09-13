// Necessary header files to use Linux Kernel functions and data structures
#include <linux/kernel.h> // For core kernel functions
#include <linux/module.h> // For module-related macros and functions
#include <linux/delay.h>  // For delay functions, although not used in this specific code
#include <linux/device.h> // For device-related operations

// Specify the license type for the module
MODULE_LICENSE("GPL");

// Declaration of a pointer to a class structure. This will be used to represent a device class.
static struct class *class;

// Initialization function: This function is executed when the module is loaded.
static int test_hello_init(void)
{
    // Create a device class named "myclass" and associate it with this module.
    // 'THIS_MODULE' is a macro that refers to the currently-loaded module.
    class = class_create(THIS_MODULE, "myclass");
    // As this is just initialization, simply return 0 indicating successful initialization.
    return 0;
}

// Cleanup function: This function is executed when the module is unloaded.
static void test_hello_exit(void)
{
    // Destroy the previously created device class.
    class_destroy(class);
}

// Macros to specify which functions should be executed upon module loading and unloading.
module_init(test_hello_init);
module_exit(test_hello_exit);
