/*------------------------------------------------------------------*
 * nx_common.h												        *	
 *																	*
 * Definiciones comunes para NR y NX                                *
 *------------------------------------------------------------------*/

#define NX_MAX_BUFF_SIZE    512     


typedef  unsigned short NX_ADDRESS; // Tipo de dato usado para la direccion NX

#define NX_ADDR_BROADCAST   0xffff
#define NX_ADDR_NETWORK     0x0000

// Nivel de Log
typedef enum {
    NX_LOG_OFF = 0,
    NX_LOG_INFO = 1,
    NX_LOG_DEBUG = 2,
    NX_LOG_ERROR = 4,
    NX_LOG_WARN = 8,
    NX_LOG_ALL = NX_LOG_INFO | NX_LOG_DEBUG | NX_LOG_ERROR | NX_LOG_WARN
} NX_LOGLEVEL;

// Identificadores de los mensajes
enum {
    ID_DATA               = 0,
    ID_ACK                = 1,
    ID_QUERY_REQUEST      = 2,
    ID_QUERY_RESP         = 3,
    ID_ROUTES             = 4,
    ID_NACK_RESEND_LATER  = 5,  // Se rechaza temporalmente porque no puede almacenar el dato, buffer lleno. El remoto debe volver a enviar el mismo mensaje mas tarde
    ID_NACK_BACKOFF       = 6,  // Se acepta el mensaje pero se le indica al remoto que aguarde un tiempo antes de continuar enviando
    ID_NACK_PERMANENT     = 7,  // Se rechaza la solicitud porque no se puede resolver
};

#define QUERY_RESPONSE_MAX_SIZE 9

// Mensaje para enviar/recibir DATOS
#define NX_DATA_MSG_HDR_SIZE 14

typedef struct {
    NX_ADDRESS      next;           // Proximo salto
    NX_ADDRESS      source;         // Origen del mensaje (cambia por salto)
    UCHAR           hopcount;       // Numero de saltos restantes
    NX_ADDRESS      dest;           // Destino del mensaje
    USHORT          msgid_dev;     // Identificador del mensaje (parte que identifica al dispositivo)
    USHORT          msgid_count;   // Identificador del mensaje (parte que identifica al mensaje)
    USHORT          len;            // Numero de bytes de datos del mensaje
    UCHAR           payload[MAX_DATA_SIZE];
    UCHAR           hopcount_total; // Numero total de saltos de extremo a extremo
} NX_DATA_MSG;

// Mensaje para consultar por una ruta
#define NX_ROUTER_QUERY_SIZE 7
typedef struct {
    USHORT dest;                // Destino del mensaje
    USHORT source;              // Origen del mensaje
    USHORT se;                  // Server por el cual se consulta
} NX_ROUTER_QUERY;

// Mensaje para responder por una ruta
#define NX_ROUTER_RESP_SIZE 9   // Tamaño de un ROUTER_RESPONSE
typedef struct {
    USHORT dest;                // Destino del mensaje
    USHORT source;              // Origen del mensaje
    USHORT se;                  // Server 
    UCHAR  cost;                // Costo que tiene el source para llegar al se
    UCHAR  hopcount;            // Numero de saltos que tiene el source hasta el se
} NX_ROUTER_RESPONSE;

// Mensaje para enviar/recibir RUTAS
#define NX_ROUTES_MSG_HDR_SIZE      6
#define NX_ROUTES_MSG_ROUTE_SIZE    4
#define NX_MAX_ROUTES               10

typedef struct {
    NX_ADDRESS  se;         // Server
    UCHAR   cost;       // Costo de la ruta
    UCHAR   hopcount;   // Numero de saltos
} NX_ROUTES_ENTRY;

typedef struct {
    NX_ADDRESS          dest;                  // Destino
    NX_ADDRESS          source;                // Origen del mensaje 
    UCHAR               count;                 // Numero de rutas
    NX_ROUTES_ENTRY     routes[NX_MAX_ROUTES]; // Rutas
} NX_ROUTES_MSG;

#define NX_ROUTES_MSG_SIZE sizeof(NX_ROUTES_MSG)

// Mensaje de confirmacion de recepcion
#define NX_ACK_SIZE 9 // Tamaño de un DATA_ACK
typedef struct {
    USHORT dest;                // Destino del mensaje
    USHORT source;              // Origen del mensaje
    USHORT msgid_dev;           // Identificador de mensaje del cual se esta enviando el ACK
    USHORT msgid_count;
} NX_ACK;

#define NX_NACK_SIZE 9 // Tamaño de un DATA_ACK
typedef struct {
    USHORT dest;                // Destino del mensaje
    USHORT source;              // Origen del mensaje
    USHORT msgid_dev;               // Identificador de mensaje del cual se esta enviando el ACK
    USHORT msgid_count;
    UCHAR  type;                // Tipo de nack
} NX_NACK;


#define INVALID_INDEX   0xffff

// Tipos de rutas 
#define ROUTE_TYPE_SE   0       // Ruta hacia un SE
#define ROUTE_TYPE_NF   1       // Ruta hacia un NF

// Ruta
typedef struct {
    int         route_type;      // Tipo de ruta ( hacia un SE o NF)

    // Parametros comunes a ambos tipos de rutas
    NX_ADDRESS  remote;          // Direccion destino
    NX_ADDRESS  next;            // Proximo salto
    BOOL        inuse;           // Bandera que indica si la entrada esta en uso
    UCHAR       hopcount;        // Numero de saltos para llegar al destino. Incluye el primer salto del NF al NR
    UCHAR       hopcount_total;  // Numero de saltos totales entre el NF y el SE
    USHORT      ticks_t0;        // Valor devuelto por la funcion de cbck de temporizacion al momento de cargar/actualizar la ruta   
    USHORT      dit_next;        // Indice del proximo mensaje a enviar. Esta referido a arreglo dit[]
    USHORT      max_ticks;       // Maxima cantidad de ticks antes de que la ruta sea descartada

    USHORT      ticks_t0_bo;     // Valor devuelto por la funcion de cbck de temporizacion al momento de recibir un ID_NACK_BACKOFF   

    // Parametros especificos de una ruta hacia un SE
    UCHAR       cost;            // Costo de la ruta
    BOOL        lost;            // Bandera que indica que la ruta se perdio
    USHORT      lost_adv_count;  // Numero de advertisments que aun se deben hacer de esta ruta antes de quitarla (solo cuando lost es TRUE)
} ROUTE_ENTRY;

typedef ROUTE_ENTRY ROUTE_ENTRY_NF;

typedef struct {
    ROUTE_ENTRY     entries[MAX_NR_ROUTE_ENTRIES];
    int             last_entry_start;                   // Al momento de recorrer las entradas buscando un mensaje expirado, aqui guarda el valor de la ultima entrada expirada. La proxima vez se comienza de last_entry_start + 1
                                                        // para lograr que aunque vuelva expirar la misma se analicen las otras tambien. Round robin

} ROUTE_TABLE;

typedef ROUTE_TABLE ROUTE_TABLE_NF;

typedef BUFFER NX_BUFFER;

typedef USHORT(*GET_CURRENT_TICKS)(USHORT *max_ticks);         // Prototipo de funcion utilizada para recuperar los ticks actuales del sistema


// DATA
int nx_build_data_msg(NX_DATA_MSG* m, UCHAR* out);
int nx_parse_data_msg(UCHAR* buf, USHORT len, NX_DATA_MSG* m);
void nx_print_data(NX_DATA_MSG* pd, char* out);

// ACK
int nx_build_ack(NX_ACK* m, UCHAR* out);
int nx_parse_ack(UCHAR* data, UINT len, NX_ACK* m);
void nx_print_ack(NX_ACK* pa, char* out);

// NACK
int nx_build_nack(NX_NACK* m, UCHAR* data);
int nx_parse_nack(UCHAR* data, UINT len, NX_NACK* m);
void nx_print_nack(NX_NACK* pa, char* out);

// ROUTE_QUERY
int  nx_build_router_query(NX_ROUTER_QUERY* m, UCHAR* data);
int  nx_parse_router_query(UCHAR* data, USHORT len, NX_ROUTER_QUERY* m);
void print_router_query(NX_ROUTER_QUERY *pq, char *out);

// ROUTE_QUERY_RESPONSE
int   nx_build_router_resp(NX_ROUTER_RESPONSE* m, UCHAR* data);
int   nx_parse_router_resp(UCHAR* data, UINT len, NX_ROUTER_RESPONSE* m);
void  print_router_query_resp(NX_ROUTER_RESPONSE *pqr, char *out);

// ROUTES
int nx_build_routes_msg(NX_ROUTES_MSG* m, UCHAR* out);
int nx_parse_routes_msg(UCHAR* buf, USHORT len, NX_ROUTES_MSG* m);
void print_routes(NX_ROUTES_MSG *pr, char *out);

// nx_misc.c
char* msg_2_str(UCHAR mtype);
UCHAR* nx_add_ushort(USHORT us, UCHAR* p);
UCHAR* nx_get_ushort(UCHAR* p, USHORT* us);
void print_buffer(char *p, int len);

// nx_timer.c
BOOL nx_time_exp(UINT ticks_t0, UINT curr_ticks, UINT max_ticks, UINT tm);