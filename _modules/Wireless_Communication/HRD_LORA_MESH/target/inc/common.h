
//#ifndef BOOL
//typedef  unsigned char BOOL;
// Tamaño del buffer de tx/rx
#define MAX_DATA_SIZE 128


typedef struct {
    UCHAR   data[MAX_DATA_SIZE];
    USHORT  data_len;
} BUFFER;

