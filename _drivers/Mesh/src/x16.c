#include "x16.h"

void trace(const char *func, char *msg, int loglevel)
{
    return;
}

USHORT swap_us(USHORT in)
{
    USHORT out;
    UCHAR *pi,*po;
    
    po = (UCHAR*)&out;
    pi = (UCHAR*)&in;
    
    po[0] = pi[1];
    po[1] = pi[0];
    
    return out;
}

UINT swap_ui(UINT in)
{
    UINT out;
    UCHAR *pi,*po;
    
    po = (UCHAR*)&out;
    pi = (UCHAR*)&in;
    
    po[0] = pi[3];
    po[1] = pi[2];
    po[2] = pi[1];    
    po[3] = pi[0];        
    
    return out;
}

USHORT htons(USHORT h)
{
    return swap_us(h);
}

UINT htonl(UINT h)
{
    return swap_ui(h);
}

USHORT ntohs(USHORT n)
{
    return swap_us(n);
}

UINT ntohl(UINT n)
{
    return swap_ui(n);
}