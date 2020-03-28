#include "includes.h"

/*
 * Dumps a block of memory as 32-bit hex words
 */
void hex_dump_32bit(const char *desc, void *addr, int bytes, int wordToHighlight) {
    
    int			wordIndex;
    uint32_t	*p = (uint32_t*)addr;

    printk (KERN_INFO "%s:", desc);
    for (wordIndex = 0; wordIndex < bytes/4; wordIndex++) {
        if ((wordIndex % 8) == 0) {
            if (wordIndex != 0)
                printk(KERN_INFO "");
            printk(KERN_INFO "  %04x ", wordIndex*sizeof(uint32_t)); 
        }   
        if (wordIndex % 8 == 4)
            printk(KERN_CONT " -");
        if (wordIndex == wordToHighlight)
            printk(KERN_CONT "*%08x", p[wordIndex]);
        else
            printk(KERN_CONT " %08x", p[wordIndex]);
    }   
    printk(KERN_INFO "");
}


