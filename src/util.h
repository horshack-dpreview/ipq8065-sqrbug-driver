#ifndef _INCL_UTIL
#define _INCL_UTIL

#define countof(x)  (sizeof(x) / sizeof((x)[0]))

extern void hex_dump_32bit(const char *desc, void *addr, int bytes, int wordToHighlight);

#endif /* #ifndef _INCL_UTIL */
