#include "includes.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Horshack");
MODULE_DESCRIPTION("Reproduce CPU Data load corruption on my Netgear X4S R7800");

static int  CountIterations = 50000;
static uint Flags = 0x00000000;
module_param(CountIterations, int, S_IRUGO | S_IWUSR);
module_param(Flags, uint, S_IRUGO | S_IWUSR);

extern int do_sqr_test(int countIterations, uint flags);

static __init int ipq8065_sqrbug_init(void)
{
    printk(KERN_INFO "ipq8065-sqrbug-driver init: Iterations=%d, Flags=0x%08x\n",
            CountIterations, Flags);
    do_sqr_test(CountIterations, Flags);
    return -1; // uncondtionally fail the load. look for result via dmesg
}

static __exit void ipq8065_sqrbug_exit(void)
{
    printk(KERN_INFO "ips8065-sqrbug-driver exit:\n");
}
module_init(ipq8065_sqrbug_init);
module_exit(ipq8065_sqrbug_exit);
