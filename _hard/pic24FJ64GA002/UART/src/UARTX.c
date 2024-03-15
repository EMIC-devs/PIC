/*************************************************************************//**
  @file     UARTX.c

  @brief    Hardware Library to use UART

  @author   Rottoli Luciano

  @version  v0.0.1  

  @date		01/03/2024  

 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "inc/gpio.h"
#include "inc/streamOut.h"
#include "inc/streamIn.h"
#include "inc/UART.{port}..h"
#include "inc/system.h"


/*==================[internal data definition]===============================*/
const streamIn_t  streamIn_Uart.{port}.  = {UART.{port}._IN_pop, UART.{port}._IN_count};
const streamOut_t streamOut_Uart.{port}. = {UART.{port}._OUT_push, UART.{port}._OUT_count};

uint8_t     UART.{port}._flowControlVar = 0;
uint8_t     UART.{port}._inverted       = 0;

UART_FIFO   UART.{port}._IN_fifo;
UART_FIFO   UART.{port}._OUT_fifo;

/*==================[public functions definition]==========================*/
void UART.{port}._init_fifo(UART_FIFO *fifo) 
{
    fifo->start = 0;
    fifo->end = 0;
    fifo->count = 0;
}

uint16_t UART.{port}._is_empty(UART_FIFO *fifo)
{
    return (fifo->count == 0);
}

uint8_t UART.{port}._is_full(UART_FIFO *fifo) 
{
    return (fifo->count == UART.{port}._MAX_BUFFER_SIZE);
}

uint16_t UART.{port}._count(UART_FIFO *fifo)
{
	return fifo->count;
}

void UART.{port}._push(UART_FIFO *fifo, char data)
{
    _U.{port}.RXIE = 0;
    _U.{port}.TXIE = 0;
    fifo->buffer[fifo->end] = data;
    fifo->end = (fifo->end + 1) % UART.{port}._MAX_BUFFER_SIZE;
    fifo->count++;
    if(fifo->count >= UART.{port}._MAX_BUFFER_SIZE)
    {
        fifo->count = UART.{port}._MAX_BUFFER_SIZE;
    }
    _U.{port}.RXIE = 1;
    _U.{port}.TXIE = 1;
}

char UART.{port}._pop(UART_FIFO *fifo) 
{
    _U.{port}.RXIE = 0;
    _U.{port}.TXIE = 0;
    char data = 0;
    data = fifo->buffer[fifo->start];
    fifo->start = (fifo->start + 1) % UART.{port}._MAX_BUFFER_SIZE;
    fifo->count--;
    _U.{port}.RXIE = 1;
    _U.{port}.TXIE = 1;
    return data;
}

char UART.{port}._peek(UART_FIFO *fifo)
{
    // Calculate the index of the last element in the FIFO
    uint16_t last_index = (fifo->start + fifo->count - 1) % UART.{port}._MAX_BUFFER_SIZE;
    // Return the last received value in the FIFO
    return fifo->buffer[last_index];
}

void UART.{port}._simplexMode(void)
{
	U.{port}.MODEbits.RTSMD=1;
	U.{port}.MODEbits.UEN1=1;
	U.{port}.MODEbits.UEN0=0;
}

void UART.{port}._flowControl(uint8_t enabled)
{
    U.{port}.MODEbits.RTSMD         =   0;
    U.{port}.MODEbits.UEN0          =   0;
    UART.{port}._flowControlVar    =   enabled;
    U.{port}.MODEbits.UEN1          =   enabled;
}

void UART.{port}._invert(uint8_t invert)
{
	U.{port}.STAbits.UTXINV =   invert;
    U.{port}.MODEbits.RXINV =   invert;
    UART.{port}._inverted =   invert;
}

void UART.{port}._bd(uint32_t uartSpeed)
{
    switch(uartSpeed)
    {
        case 600:
        case 1200:
        case 2400:
        case 4800:
        case 9600:
        case 14400:
        case 19200:
        case 28800:
        case 38400:
        case 56000:
        case 57600:
            U.{port}.BRG = ((FCY / (16 * uartSpeed)) - 1);
            break;

#ifdef SYSTEM_FREQ
#if SYSTEM_FREQ > 8000000
        case 115200:
        case 128000:
        case 153600:
        case 230400:
        case 256000:
            U.{port}.BRG = ((FCY / (16 * uartSpeed)) - 1);
            break;
#endif
#endif
        default:
            U.{port}.BRG = ((FCY / ((uint16_t)16 * 9600)) - 1);
        break;
    }
}

void UART.{port}._init(void)
{
	__builtin_write_OSCCONL(OSCCON & 0xBF);
	/* Configure Input Functions (Table 10-2)) */

    RPOUT_.{name}._TX =_RPOUT_U.{port}.TX;
    _U.{port}.RXR = RPIN_.{name}._RX;

	#ifdef RPIN_.{name}._CTS
		_U.{port}.CTSR = RPIN_.{name}._CTS;
	#endif

	#ifdef RPOUT_.{name}._RTS
		RPOUT_.{name}._RTS = _RPOUT_U.{port}.RTS;
	#endif

	/* Configure Output Functions (Table 10-3) */

	/* Lock Registers */
	__builtin_write_OSCCONL(OSCCON | 0x40);

	/* Bit3 16 clocks per bit period*/
	U.{port}.MODEbits.BRGH = 0;
    
    UART.{port}._bd((uint32_t).{baud}.);

 	U.{port}.MODE = 0;                     //8-bit data, no parity, 1 stop bit
    U.{port}.MODEbits.UARTEN = 1;          //enable the module
	U.{port}.STAbits.UTXISEL0=0;
	U.{port}.STAbits.UTXISEL1=0;

	/* Enable transmission*/
 	U.{port}.STAbits.UTXEN = 1; 

    _U.{port}.RXIE = 1;
    _U.{port}.TXIE = 1;
    UART.{port}._init_fifo(&UART.{port}._IN_fifo);
    UART.{port}._init_fifo(&UART.{port}._OUT_fifo);
}

void UART.{port}._OFF(void)
{
    U.{port}.MODEbits.UARTEN = 0;
 	U.{port}.STAbits.UTXEN = 0; 
    _U.{port}.RXIE = 0;
    _U.{port}.TXIE = 0;
}

void UART.{port}._ON(void)
{
    U.{port}.MODEbits.UARTEN = 1;
 	U.{port}.STAbits.UTXEN = 1;
    _U.{port}.RXIE = 1;
    _U.{port}.TXIE = 1;
	UART.{port}._init_fifo(&UART.{port}._IN_fifo);
    UART.{port}._init_fifo(&UART.{port}._OUT_fifo);
}

/**
 * @brief UART Transmit Interrupt Service Routine.
 *
 * This ISR handles the transmit interrupt for the UART module. It clears the
 * TX interrupt flag and transmits data from the output FIFO buffer as long as
 * there is data available in the buffer.
 */
void __attribute__((interrupt(auto_psv))) _U.{port}.TXInterrupt( void )
{
	/* Clear TX interrupt flag */
	_U.{port}.TXIF = 0;

	while(UART.{port}._OUT_fifo.count)
	{
		if(!U.{port}.STAbits.UTXBF)
			U.{port}.TXREG = UART.{port}._pop(&UART.{port}._OUT_fifo);
		else
        {
            return;
        }
	}
}

/**
 * @brief UART Receive Interrupt Service Routine.
 *
 * This ISR handles the receive interrupt for the UART module. It clears the
 * RX interrupt flag and reads data from the receive register, pushing it into
 * the input FIFO buffer.
 */
void __attribute__((interrupt(auto_psv))) _U.{port}.RXInterrupt( void )
{
	char d;
   /* Clear RX interrupt flag */
    _U.{port}.TXIF = 0;
	if(U.{port}.STAbits.OERR)			//If an overflow occurred, clean the flag, otherwise RXREG doesn't update
    {
        U.{port}.STAbits.OERR = 0;	    //TODO: generar evento de error
    } 

	while (U.{port}.STAbits.URXDA)	    //While there is still data in the register
	{
		d = U.{port}.RXREG ;  
		UART.{port}._push(&UART.{port}._IN_fifo, d) ;		//Push data into the input buffer
	}
    EMIC:ifdef(UART.{port}._CALLBACK_RX)
    ISR_UART.{port}._CALLBACK(d);
    EMIC:endif
	return;
}

char UART.{port}._IN_pop(void)
{
    return UART.{port}._pop(&UART.{port}._IN_fifo);
}

uint16_t UART.{port}._IN_count(void)
{
    return UART.{port}._IN_fifo.count;
}

void UART.{port}._OUT_push(char d)
{
    UART.{port}._push(&UART.{port}._OUT_fifo, d);
}

uint16_t UART.{port}._OUT_count(void)
{
    return UART.{port}._MAX_BUFFER_SIZE - UART.{port}._OUT_fifo.count;
}