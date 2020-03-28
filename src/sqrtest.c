#include "includes.h"

static mp_digit MpIntInputDigits[74];
static mp_digit SqrResult[148], ExpectedSqrResult[148];


/*
 * Do the squaring test until it fails or until we've done
 * an arbitrary-large number of attempts. Sometimes this
 * routine must be executed multiple times to fail, so call
 * it from a script that loops until we hit the corruption
 */
int do_sqr_test(int countIterations, uint flags) {

#define FLAG_SET(_bits)     (flags & (_bits))
#define FLAG_CLEAR(_bits)   ((flags & (_bits))==0)
    int        iteration, indexMismatch, ret;
    mp_int      a;

    ret = 0;
    for (iteration=0; iteration<countIterations; iteration++) {

        // build mp_int structure
        a.used = countof(MpIntInputDigits);
        a.alloc = countof(SqrResult);
        a.sign  = MP_ZPOS;
        memcpy(a.dp, MpIntInputDigits, sizeof(MpIntInputDigits));

        // perform squaring operation
        if (FLAG_SET(0x00000002))
            local_irq_disable();
        fast_s_mp_sqr(&a, &a, SqrResult);
        if (FLAG_SET(0x00000002))
            local_irq_enable();

        // see if the failure occurred by 
        if (memcmp(SqrResult, ExpectedSqrResult, sizeof(SqrResult))) { 

            // issue hit. find word with wrong data
            for (indexMismatch=0; indexMismatch<countof(SqrResult); indexMismatch++) {
                if (SqrResult[indexMismatch] != ExpectedSqrResult[indexMismatch])
                    break;
            }
            // print results
            printk(KERN_INFO "ipq8065-sqrbug-driver: Mismatch on Iteration %d - Index = %d, Byte Offset = 0x%04x\n",
                   iteration, indexMismatch,  indexMismatch*sizeof(mp_digit));
            printk(KERN_INFO "Expected Word = 0x%08x, Actual Word = 0x%08x, &a.dp=0x%08x \n", 
                   (uint32_t)(ExpectedSqrResult[indexMismatch]),
                   (uint32_t)(SqrResult[indexMismatch]),
                   (uint32_t)(uintptr_t)a.dp);
            hex_dump_32bit("Expected Result", ExpectedSqrResult, sizeof(ExpectedSqrResult), indexMismatch);
            hex_dump_32bit("Actual Result", SqrResult, sizeof(SqrResult), indexMismatch);
            ret = 1;
            break;
        }

        if (FLAG_CLEAR(0x00000001))
            yield();
    }
    return ret;
}


