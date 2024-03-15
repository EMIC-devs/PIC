#ifndef __CONVERSIONFUNCTIONS_C__
#define __CONVERSIONFUNCTIONS_C__

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "inc/conversionFunctions.h"

float ato_float(char* number)
{
    return (float)atof(number);
}

double ato_double(char* number)
{
    return atof(number);
}

void float_to_ascii(char* string, float number, uint8_t n)
{
    snprintf(string, "%1.2f", (double)number, n);                 //TODO: falta probar  
}

void double_to_ascii(char* string, double number, uint8_t n)
{
    snprintf(string, n, "%1.2f", number);                 //TODO: falta probar  
}

void uint8_t_to_ascii(uint8_t number, char* string, uint8_t n)
{
    snprintf(string, n, "%hu", number);                 //8bits are short data type   
}

void uint16_t_to_ascii(uint16_t number, char* string, uint8_t n)
{
    snprintf(string, n, "%u", number);                  //16bits are standart data type           
}

void uint32_t_to_ascii(uint32_t number, char* string, uint8_t n)
{
    snprintf(string, n, "%lu", number);                 //32bits are long data type   
}

void uint64_t_to_ascii(uint64_t number, char* string, uint8_t n)
{
    snprintf(string, n, "%llu", number);                 //64bits are long long data type   
}

void int8_t_to_ascii(int8_t number, char* string, uint8_t n)
{
    snprintf(string, n, "%hd", number);                 //8bits are short data type   
}

void int16_t_to_ascii(int16_t number, char* string, uint8_t n)
{
    snprintf(string, n, "%d", number);                  //16bits are standart data type           
}

void int32_t_to_ascii(int32_t number, char* string, uint8_t n)
{
    snprintf(string, n, "%ld", number);                 //32bits are long data type   
}

void int64_t_to_ascii(int64_t number, char* string, uint8_t n)
{
    snprintf(string, n, "%lld", number);                 //64bits are long long data type   
}

uint8_t ato_uint8_t(char* string)
{
    return (uint8_t)atoi(string);
}

uint16_t ato_uint16_t(char* string)
{
    return (uint16_t)atoi(string);
}

uint32_t ato_uint32_t(char* string)
{
    return (uint32_t)atol(string);
}

uint64_t ato_uint64_t(char* string)
{  
    return (uint64_t)atoll(string);
}

int8_t ato_int8_t(char* string)
{
    return (int8_t)atoi(string);
}

int16_t ato_int16_t(char* string)
{
    return atoi(string);
}

int32_t ato_int32_t(char* string)
{
    return atol(string);
}

int64_t ato_int64_t(char* string)
{
    return atoll(string);
}

#endif //__CONVERSIONFUNCTIONS_C__