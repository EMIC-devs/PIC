#ifndef __CONVERSIONFUNCTIONS_H__
#define __CONVERSIONFUNCTIONS_H__
inline float ato_float(char* number);                           //string to float
inline double ato_double(char* number);                         //string to double

inline void float_to_ascii(char* string, float number);
inline void double_to_ascii(char* string, double number);

inline void uint8_t_to_ascii ( uint8_t number, char* string, uint8_t n);     //uint8_t to string
inline void uint16_t_to_ascii(uint16_t number, char* string, uint8_t n);   //uint16_t to string
inline void uint32_t_to_ascii(uint32_t number, char* string, uint8_t n);   //uint32_t to string
inline void uint64_t_to_ascii(uint64_t number, char* string, uint8_t n);   //uint64_t to string
inline void int8_t_to_ascii  (  int8_t number, char* string, uint8_t n);       //int8_t to string
inline void int16_t_to_ascii ( int16_t number, char* string, uint8_t n);     //int16_t to string
inline void int32_t_to_ascii ( int32_t number, char* string, uint8_t n);     //int32_t to string
inline void int64_t_to_ascii ( int64_t number, char* string, uint8_t n);     //int64_t to string

inline uint8_t ato_uint8_t(char* string);                         //string to uint8_t
inline uint16_t ato_uint16_t(char* string);                       //string to uint16_t
inline uint32_t ato_uint32_t(char* string);                       //string to uint32_t
inline uint64_t ato_uint64_t(char* string);                       //string to uint64_t
inline int8_t ato_int8_t(char* string);                           //string to int8_t
inline int16_t ato_int16_t(char* string);                         //string to int16_t
inline int32_t ato_int32_t(char* string);                         //string to int32_t
inline int64_t ato_int64_t(char* string);                         //string to int64_t

#endif //__CONVERSIONFUNCTIONS_H__