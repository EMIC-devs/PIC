#ifndef __CONVERSIONFUNCTIONS_H__
#define __CONVERSIONFUNCTIONS_H__

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define float_to_ascii(string,number,n)     snprintf(string, n, "%1.2f", (double)number)
#define double_to_ascii(string,number,n)    snprintf(string, n, "%1.2f", number)
#define uint8_t_to_ascii(number,string,n)   snprintf(string, n, "%hu", number)
#define uint16_t_to_ascii(number,string,n)  snprintf(string, n, "%u", number)
#define uint32_t_to_ascii(number,string,n)  snprintf(string, n, "%lu", number)
#define uint64_t_to_ascii(number,string,n)  snprintf(string, n, "%llu", number)
#define int8_t_to_ascii(number,string,n)    snprintf(string, n, "%hd", number)
#define int16_t_to_ascii(number,string,n)   snprintf(string, n, "%d", number)
#define int32_t_to_ascii(number,string,n)   snprintf(string, n, "%ld", number)
#define int64_t_to_ascii(number,string,n)   snprintf(string, n, "%lld", number)

#define ato_float(number)       (float)atof(number)
#define ato_double(number)      atof(number)
#define ato_uint8_t(string)     (uint8_t)atoi(string)
#define ato_uint16_t(string)    (uint16_t)atoi(string)
#define ato_uint32_t(string)    (uint32_t)atol(string)
#define ato_uint64_t(string)    (uint64_t)atoll(string)
#define ato_int8_t(string)      (int8_t)atoi(string)
#define ato_int16_t(string)      atoi(string)
#define ato_int32_t(string)     atol(string)
#define ato_int64_t(string)     atoll(string)

// inline float ato_float(char* number);                           //string to float
// inline double ato_double(char* number);                         //string to double

// inline void float_to_ascii(char* string, float number);
// inline void double_to_ascii(char* string, double number);

// inline void uint8_t_to_ascii ( uint8_t number, char* string, uint8_t n);     //uint8_t to string
// inline void uint16_t_to_ascii(uint16_t number, char* string, uint8_t n);   //uint16_t to string
// inline void uint32_t_to_ascii(uint32_t number, char* string, uint8_t n);   //uint32_t to string
// inline void uint64_t_to_ascii(uint64_t number, char* string, uint8_t n);   //uint64_t to string
// inline void int8_t_to_ascii  (  int8_t number, char* string, uint8_t n);       //int8_t to string
// inline void int16_t_to_ascii ( int16_t number, char* string, uint8_t n);     //int16_t to string
// inline void int32_t_to_ascii ( int32_t number, char* string, uint8_t n);     //int32_t to string
// inline void int64_t_to_ascii ( int64_t number, char* string, uint8_t n);     //int64_t to string

// inline uint8_t ato_uint8_t(char* string);                         //string to uint8_t
// inline uint16_t ato_uint16_t(char* string);                       //string to uint16_t
// inline uint32_t ato_uint32_t(char* string);                       //string to uint32_t
// inline uint64_t ato_uint64_t(char* string);                       //string to uint64_t
// inline int8_t ato_int8_t(char* string);                           //string to int8_t
// inline int16_t ato_int16_t(char* string);                         //string to int16_t
// inline int32_t ato_int32_t(char* string);                         //string to int32_t
// inline int64_t ato_int64_t(char* string);                         //string to int64_t

#endif //__CONVERSIONFUNCTIONS_H__