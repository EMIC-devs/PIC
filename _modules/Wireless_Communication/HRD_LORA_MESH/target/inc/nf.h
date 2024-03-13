/*------------------------------------------------------------------*
 * nf_api.h													        *	
 *																	*
 * API del modulo NF                                                *
 *------------------------------------------------------------------*/

// Nivel de Log
typedef  NX_LOGLEVEL NF_LOGLEVEL;


typedef struct {
    UINT      max_n_retry_data;       // Numero de reintentos al momento de enviar un DATA
    UINT      max_n_retry_query;      // Numero de reintentos al momento de enviar un QUERY
    UINT      max_ticks_calm;         // Numero de ticks entre dos sucesivas tx
    UINT      max_ticks_backoff;      // Numero de ticks que aguarda para reintentar una tx luego de recibir un NACK_TEMPORAL
} NF_TX_PARAMS;

typedef struct {
    UINT      max_ticks_resp;         // Ticks que se debe aguardar por las respuestas de los NR a un QUERY REQUEST
    UINT      max_ticks_route;        // Ticks que dura una ruta como valida
    UINT      max_ticks_ack;          // Ticks que se debe aguardar un ACK
} NF_RX_PARAMS;

// Configuracion
typedef struct {
    NX_ADDRESS          local;              // Direccion local del dispositivo
    NF_TX_PARAMS        tx_params;          // Parametros de transmision
    NF_RX_PARAMS        rx_params;          // Parametros de recepcion
    UCHAR               se_host_bits;       // Numero de bits del NX_ADDRESS utilizados identificar hosts en un grupo
} NF_CONFIG;

typedef struct {
    GET_CURRENT_TICKS   get_current_ticks;  // Recupera la cuenta actual de ticks
    PHY_LISTEN_START    phy_listen_start;   // Funcion de la capa inferior utilizada para ponerla en modo escucha
    PHY_LISTEN_STOP     phy_listen_stop;    // Funcion de la capa inferior utilizada para detener el modo escucha
    PHY_SEND            phy_send;           // Funcion para enviar datos por la phy 
    PHY_STATUS          phy_status;         // Funcion de la capa inferior utilizada para recuperar el estado
} NF_CALLBACKS;



// Agrupa todas las variables asociadas al estado de una transmision
typedef struct {
    BOOL        ready;              // Bandera que indica que la transimision fue finalizada
    BOOL        ok;                 // Bandera que indica si el resultado de la transmision fue correcto o no
    NX_BUFFER   buffer;             // Buffer que contiene el mensaje a enviar
    NX_ADDRESS  remote;             // Destino del mensaje de datos 
    NX_ADDRESS  next;               // Proximo salto a donde enviar el mensaje
    USHORT      tick_t0;            // Valor de tick leido al momento de comenzar a esperar una respuesta a una tx
    USHORT      ticks_t0_back_off;  // Valor de tick leido al momento de recibir un NACK_TEMPORAL
    USHORT      next_msgid;         // Valor del proximo msgid a utilizar
    USHORT      pending_msgid_dev;  // Identificador del mensaje que espera confirmacion
    USHORT      pending_msgid_count;
    USHORT      tick_delay;         // 
    USHORT      tick_calm;          // Ticks donde se recibio el ultimo ack
} TX_STATUS;

typedef struct {
    BOOL        ready;              // Bandera que indica la existencia de un nuevo mensaje recibido
    USHORT      ticks_t0;           // Valor que devolvio el contador de ticks cuando comenzo la rx
    NX_BUFFER   buffer;             // Buffer donde se deposita el payload recibido
    USHORT      msg_id_dev;         // Identificador del mensaje
    USHORT      msg_id_count;
    USHORT      max_ticks;          // Maxima cantidad de ticks que deben pasar antes de finalizar la rx continua 
    BOOL        stop;               // Bandera que indica que se debe tener la recepcion (la setea la app)
    BOOL        refresh;            // Si esta en true, cada vez que se recibe un mensaje de datos, se reinicia el temporizador de espera
} RX_STATUS;

typedef struct {
    RX_STATUS   rx_status;
    TX_STATUS   tx_status;
} NF_STATUS;

#define NF_ERROR_NO_ERROR           0
#define NF_ERROR_INVALID_PARAMS     -1
#define NF_ERROR_INVALID_PHY        -2
#define NF_ERROR_PHY                -3
#define NF_ERROR_ALREADY_INITED     -4
#define NF_ERROR_NO_INITED          -5
#define NF_ERROR_INVALID_STATE      -6
#define NF_ERROR_ALREADY_LOCKED     -7
#define NF_ERROR_INVALID_ADDRESS    -8
#define NF_ERROR_DATA_TO_BIG        -9
#define NF_ERROR_ERROR_RECV_PHY     -10   // La capa phy rechazo pasar a modo recepcion
#define NF_ERROR_INIT_ERROR -11
#define NF_ERROR_BUSY               -12
#define NF_ERROR_UNINITIALIZED      -13
#define NF_ERROR_NO_DATA            -14

/*------------------------------------------------------------------*
 * nf_init(loglevel, cbck, config)                                  *
 *                                                                  *
 * Entrada:   loglevel            Nivel de log                      *
 *            cbck                Funciones de callback             *
 *            config              Configuracion a utilizar          *
 *																	*
 * Salida:    No posee                                              *
 *																	*
 * Retorno:   NF_ERROR_NO_ERROR o != NF_ERROR_NO_ERROR              * 
 *																	*
 * Descripcion:                                                     *
  *																	*
 * Inicializa el modulo NF                                          *
 *------------------------------------------------------------------*/
int nf_init(NF_LOGLEVEL loglevel, NF_CONFIG* nf_config, NF_CALLBACKS* cbck);

/*------------------------------------------------------------------*
 * nf_term()                                                        *
 *                                                                  *
 * Entrada:   No posee                                              *
 *																	*
 * Salida:    No posee                                              *
 *																	*
 * Retorno:   No posee                                              *
 *																	*
 * Descripcion:                                                     *
 *																	*
 * Deinicializa el modulo NF                                        *
 *------------------------------------------------------------------*/
void nf_term();

/*------------------------------------------------------------------*
 * nf_send(remote, data, len)                                       *
 *                                                                  *
 * Entrada:   remote              Destinatario del mensaje          *
 *            data                Mensaje                           *
 *            len                 Numero de bytes del mensaje       *
 *																	*
 * Salida:    No posee                                              *
 *																	*
 * Retorno:   NF_ERROR_NO_ERROR o != NF_ERROR_NO_ERROR              * 
 *																	*
 * Descripcion:                                                     *
 *																	*
 * Envia un mensaje al remoto                                       *
 *------------------------------------------------------------------*/
int nf_send(NX_ADDRESS remote, UCHAR *data, UCHAR len);

/*------------------------------------------------------------------*
 * nf_recv_start(max_ticks, refresh)                                *
 *                                                                  *
 * Entrada:   max_ticks     Ticks que se debera estar en modo escu- *
 *                          cha                                     * 
 *            refresh       Si es true, cada mensaje que se recibe  *
 *                          reinicia el tiempo de espera            *
 *																	*
 * Salida:    No posee                                              *
 *																	*
 * Retorno:   NF_ERROR_NO_ERROR o != NF_ERROR_NO_ERROR              * 
 *																	*
 * Descripcion:                                                     *
 *																	*
 * Pone al modulo NF a escuchar de manera continua                  *
 *------------------------------------------------------------------*/
int nf_recv_start(USHORT max_ticks, BOOL refresh);

/*------------------------------------------------------------------*
 * nf_recv_stop()                                                   *
 *                                                                  *
 * Entrada:   No posee                                              *
 *																	*
 * Salida:    No posee                                              *
 *																	*
 * Retorno:   NF_ERROR_NO_ERROR o != NF_ERROR_NO_ERROR              * 
 *																	*
 * Descripcion:                                                     *
 *																	*
 * Deshabilita la recepcion de mensajes                             *
 *------------------------------------------------------------------*/
int nf_recv_stop();

/*------------------------------------------------------------------*
 * nf_poll()                                                        *
 *                                                                  *
 * Entrada:   No posee                                              *
 *																	*
 * Salida:    No posee                                              *
 *																	*
 * Retorno:   No posee                                              *
 *																	*
 * Descripcion:                                                     *
 *																	*
 * Poleo del modulo                                                 *
 *------------------------------------------------------------------*/
void nf_poll();

int nf_status(NF_STATUS* nf_status);