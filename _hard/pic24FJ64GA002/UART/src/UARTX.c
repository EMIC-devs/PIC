/*************************************************************************//**
  @file     UARTX.c

  @brief    Hardware Library to use UART

  @author   Rottoli Luciano

  @version  v0.0.1  

  @date		01/03/2024  

 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include "inc/gpio.h"
#include "inc/UART.{port}..h"

/*==================[internal data definition]===============================*/
static UART_FIFO   UART.{port}._IN_fifo;
static UART_FIFO   UART.{port}._OUT_fifo;

/*==================[public functions definition]==========================*/
/**
 * @brief Initializes the UART FIFO.
 *
 * This function initializes a First In, First Out (FIFO) for use with the UART.
 *
 * @param fifo Pointer to the UART FIFO to be initialized.
 */
void UART.{port}._init_fifo(const UART_FIFO *fifo) 
{
    fifo->start = 0;
    fifo->end = 0;
    fifo->count = 0;
}

/**
 * @brief Checks if the UART FIFO is empty.
 *
 * This function checks if the UART FIFO is empty.
 *
 * @param fifo Pointer to the UART FIFO to be checked.
 * @return Returns 1 if the FIFO is empty, 0 otherwise.
 */
uint16_t UART.{port}._is_empty(const UART_FIFO *fifo)
{
    return (fifo->count == 0);
}

/**
 * @brief Checks if the UART FIFO is full.
 *
 * This function checks if the UART FIFO is full.
 *
 * @param fifo Pointer to the UART FIFO to be checked.
 * @return Returns 1 if the FIFO is full, 0 otherwise.
 */
uint8_t UART.{port}._is_full(const UART_FIFO *fifo) 
{
    return (fifo->count == UART.{port}._MAX_BUFFER_SIZE);
}

/**
 * @brief Gets the number of elements in the UART FIFO.
 *
 * This function returns the current number of elements in the UART FIFO.
 *
 * @param fifo Pointer to the UART FIFO from which the count will be obtained.
 * @return Number of elements in the UART FIFO.
 */
uint16_t UART.{port}._count(const UART_FIFO *fifo)
{
	return fifo->count;
}

/**
 * @brief Pushes data into the UART FIFO.
 *
 * This function pushes a byte of data into the UART FIFO.
 *
 * @param fifo Pointer to the UART FIFO where the data will be pushed.
 * @param data The byte of data to be pushed into the FIFO.
 */
void UART.{port}._push(const UART_FIFO *fifo, char data)
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

/**
 * @brief Pops data from the UART FIFO.
 *
 * This function pops a byte of data from the UART FIFO.
 *
 * @param fifo Pointer to the UART FIFO from which the data will be popped.
 * @return The byte of data popped from the FIFO.
 */
char UART.{port}._pop(const UART_FIFO *fifo) 
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

/**
 * @brief Peeks at the last received value in the UART input FIFO.
 *
 * This function retrieves the last received value from the UART input FIFO
 * without removing it from the FIFO.
 *
 * @return The last received value in the UART input FIFO.
 */
char UART.{port}._peek(const UART_FIFO *fifo)
{
    // Calculate the index of the last element in the FIFO
    uint16_t last_index = (fifo->start + fifo->count - 1) % UART.{port}._MAX_BUFFER_SIZE;
    // Return the last received value in the FIFO
    return fifo->buffer[last_index];
}

/**
 * @brief Configures UART for simplex mode.
 *
 * This function configures the UART for simplex mode by setting the necessary
 * control bits in the UART registers.
 */
void UART.{port}._simplexMode(void)
{
	U.{port}.MODEbits.RTSMD=1;
	U.{port}.MODEbits.UEN1=1;
	U.{port}.MODEbits.UEN0=0;
}

/**
 * @brief Configures UART flow control.
 *
 * This function configures UART flow control based on the provided parameter.
 *
 * @param enabled Flag indicating whether flow control is enabled (1) or disabled (0).
 */
void UART.{port}._flowControl(uint8_t enabled)
{
    U.{port}.MODEbits.RTSMD         =   0;
    U.{port}.MODEbits.UEN0          =   0;
    UART.{port}._flowControlVar    =   enabled;
    U.{port}.MODEbits.UEN1          =   enabled;
}

/**
 * @brief Inverts UART signals.
 *
 * This function inverts UART signals based on the provided parameter.
 *
 * @param invert Flag indicating whether to invert UART signals (1) or not (0).
 */
void UART.{port}._invert(uint8_t invert)
{
	U.{port}.STAbits.UTXINV =   invert;
    U.{port}.MODEbits.RXINV =   invert;
    UART.{port}._inverted =   invert;
}

/**
 * @brief Configures the baud rate for UART communication.
 *
 * This function configures the baud rate for UART communication based on the provided speed.
 *
 * @param uartSpeed The desired baud rate for UART communication.
 *
 * The function uses the provided baud rate to set the Baud Rate Generator (BRG)
 * for the UART module. It checks if the desired baud rate is one of the commonly
 * used values and calculates the appropriate BRG value. If the provided baud rate
 * is not in the predefined list, it defaults to a baud rate of 9600.
 */
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
            U.{port}.BRG = ((FCY / (16 * 9600)) - 1);
        break;
    }
}

/**
 * @brief Initializes the UART module.
 *
 * This function initializes the UART module, configuring input and output functions,
 * setting the baud rate, and enabling the module for communication.
 */
void UART.{port}._init(void)
{
	__builtin_write_OSCCONL(OSCCON & 0xBF);
	/* Configure Input Functions (Table 10-2)) */

    RPOUT_U.{port}._TX =_RPOUT_U.{port}.TX;
    _U.{port}.RXR = RPIN_U.{port}._RX;

	#ifdef RPIN_U.{port}.CTS
		_U.{port}.CTSR = RPIN_U.{port}._CTS
	#endif

	#ifdef RPOUT_U.{port}.RTS
		RPOUT_U.{port}._RTS = _RPOUT_U.{port}.RTS
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

/**
 * @brief Turns off the UART module.
 *
 * This function turns off the UART module by disabling UARTEN and UTXEN, and
 * also disables RX and TX interrupts.
 */
void UART.{port}._OFF(void)
{
    U.{port}.MODEbits.UARTEN = 0;
 	U.{port}.STAbits.UTXEN = 0; 
    _U.{port}.RXIE = 0;
    _U.{port}.TXIE = 0;
}

/**
 * @brief Turns on the UART module.
 *
 * This function turns on the UART module by enabling UARTEN and UTXEN, and
 * also enables RX and TX interrupts. Additionally, it initializes the input
 * and output FIFO buffers.
 */
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
 * @brief Polls the UART for transmitting data.
 *
 * This function checks if the output FIFO is not empty and the UART
 * transmit buffer is not full. If both conditions are met, it initiates
 * the transmission by sending data from the output FIFO to the UART transmit register.
 * The actual transmission process may continue in the UART transmit interrupt service routine (ISR).
 *
 * @note This function is a polling mechanism for initiating data transmission.
 * Subsequent data transmission may occur in the UART transmit ISR.
 * It should be called periodically to ensure timely data transmission.
 */
void UART.{port}._Poll(void)
{
    if(!UART.{port}._is_empty(&UART.{port}._OUT_fifo) && !U_{puerto}_STAbits.UTXBF)
    {
        U.{port}.TXREG = UART.{port}._pop(&UART.{port}._OUT_fifo);
    }
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
	U.{port}.TXIF = 0;

	while(UART.{port}._OUT_fifo.count)
	{
		if(!U.{port}.STAbits.UTXBF)
			U.{port}.TXREG = UART.{port}._pop(&UART.{port}._OUT_fifo);
		else
			return;
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
    U.{port}.TXIF = 0;
	if(U.{port}.STAbits.OERR)			//If an overflow occurred, clean the flag, otherwise RXREG doesn't update
    {
        U.{port}.STAbits.OERR = 0;	    //TODO: generar evento de error
    } 

	while (U_.{port}.STAbits.URXDA)	    //While there is still data in the register
	{
		d = U.{port}.RXREG ;  
		UART.{port}._push(&UART.{port}._IN_fifo, d) ;		//Push data into the input buffer
	}	
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