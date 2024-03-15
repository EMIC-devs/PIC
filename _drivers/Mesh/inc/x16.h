#include <stdio.h>
#include <string.h>

typedef unsigned char   UCHAR;
typedef unsigned short  USHORT;
typedef unsigned char   BOOL;
typedef unsigned int    UINT;
typedef unsigned long   ULONG;

#define TRUE	1
#define FALSE	0

void trace(const char *func, char *msg, int loglevel);

USHORT htons(USHORT h);
UINT htonl(UINT h);
USHORT ntohs(USHORT n);
UINT ntohl(UINT n);

extern char msg[256];

