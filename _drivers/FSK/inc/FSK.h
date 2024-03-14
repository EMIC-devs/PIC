#ifndef __FSK_H__
#define __FSK_H__

#include "RFM69.h"

enum EstadosRADIO
{
	RF_WAIT,			// Espera datos para transmitir o rssi
	RF_TX,				// Transmite los datos pendientes
	RF_RX,				// Lee los paquetes recibidos y devuelve el ACK.
	RF_SLEEP,			// Al salir de este, ejecuta un mensaje de wakeup al otro dispositivo.
};

enum EstadosTX
{
	TX_IN,				// Pone el chip en estado TX.
	TX_SENDING_DATA,	// Comienza a transmitir el paquete.
	TX_WAITING_ACK		// Espera a recibir un CRC OK.
};

enum EstadosRX
{
	RX_IN,				// Lee el paquete recibido.
	RX_SEND_ACK_IN,		// Cambia al modo TX para transmitir el ACK.
	RX_SENDING_ACK		// Transmite el CRC OK.
};

enum Sending_status
{
	TX_NO_ACK = -1,
	TX_SENDING = 0,
	TX_AVAILABLE = 1
};

void FSK_Init(void);
EMIC:define(inits.FSK_Init,FSK_Init)

void SendFSKMessage(uint8_t* data, uint8_t length);		//Send data, return if the data could be transmitted

uint8_t ReadFSKMessage(void);							//Read the data from RFM69, and pass this to the api.

int8_t Sending_Available(void);							//Return true if there isn't sending data.
uint8_t Data_Available(void);							//Return true if there are data avaiable to read.

uint8_t Read_Data(uint8_t* data);						//Return data and the data's length.

void FSK_Sleep(void);									//Puts the radio to sleep.
void FSK_WakeUp(void);								    //Puts the radio to wakeup.

void FSK_Poll(void);
EMIC:define(polls.FSK_Poll,FSK_Poll)
#endif