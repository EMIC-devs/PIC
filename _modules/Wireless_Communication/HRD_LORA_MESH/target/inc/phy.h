typedef BUFFER PHY_BUFFER;
typedef UCHAR RX_QUALITY; 

#define MAX_RX_QUALITY 255 // Maxima calidad posible

typedef struct {
    BOOL        tx_ready;           // La transimision solicitada finalizo 
    BOOL        tx_ok;              // Indica si la transimision fue satisfactoria o no
    
    BOOL        rx_ready;           // La recepcion finalizo 
    BOOL        rx_ok;              // Indica si el dato recibio esta corrupto o no
    PHY_BUFFER  rx_buffer;          // Dato recibido  
    RX_QUALITY  rx_quality;         // Calidad con la que se recibio el dato
} PHY_STATUS_t;


typedef int (*PHY_SEND)(UCHAR *data, UCHAR data_len);

typedef int (*PHY_LISTEN)(BOOL start);

typedef int (*PHY_LISTEN_START)(BOOL cont);

typedef void (*PHY_LISTEN_STOP)();

// 
typedef int (*PHY_STATUS)(PHY_STATUS_t *p_status);

#define PHY_ERROR_NO_ERROR 0

#define PHY_MAX_DATA_SIZE 256