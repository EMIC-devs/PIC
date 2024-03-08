#ifndef _STREAMOUT_H_
#define _STREAMOUT_H_
#include <stdarg.h>
#include <stdio.h>
#include <xc.h>
typedef struct streamOut_S
{
    void (*put)(char);
    uint16_t (*getAvailable)(void);

} streamOut_t;

void sendDataToStream(const streamOut_t*, char*,va_list);

#endif