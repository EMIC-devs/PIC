/*************************************************************************//**
  @file     UARTX.c

  @brief    Hardware Library to use UART

  @author   Rottoli Luciano

  @version  v0.0.1  

  @date		01/03/2024    

 ******************************************************************************/
#ifndef _UART.{port}._H_
#define _UART.{port}._H_

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "streamOut.h"
#include "streamIn.h"

/*==================[macros and definitions]=================================*/
#define UART.{port}._MAX_BUFFER_SIZE .{BufferSize}.

typedef struct {
    char buffer[UART.{port}._MAX_BUFFER_SIZE];
    uint16_t start;      // Pointer to the start of the queue
    uint16_t end;        // Pointer to the end of the queue
    uint16_t count;      // Count of data elements in the queue
} UART_FIFO;

/*==================[external data definition]===============================*/
extern uint8_t     UART.{port}._flowControlVar;
extern uint8_t     UART.{port}._inverted;

extern  UART_FIFO   UART.{port}._IN_fifo;
extern  UART_FIFO   UART.{port}._OUT_fifo;

/*==================[public functions definition]==========================*/

/**
 * @brief Gets the number of elements in the UART FIFO.
 *
 * This function returns the current number of elements in the UART FIFO.
 *
 * @param fifo Pointer to the UART FIFO from which the count will be obtained.
 * @return Number of elements in the UART FIFO.
 */
uint16_t UART.{port}._count(UART_FIFO *fifo);

/**
 * @brief Checks if the UART FIFO is empty.
 *
 * This function checks if the UART FIFO is empty.
 *
 * @param fifo Pointer to the UART FIFO to be checked.
 * @return Returns 1 if the FIFO is empty, 0 otherwise.
 */
uint16_t UART.{port}._is_empty(UART_FIFO *fifo);

/**
 * @brief Checks if the UART FIFO is full.
 *
 * This function checks if the UART FIFO is full.
 *
 * @param fifo Pointer to the UART FIFO to be checked.
 * @return Returns 1 if the FIFO is full, 0 otherwise.
 */
uint8_t UART.{port}._is_full(UART_FIFO *fifo);

/**
 * @brief Initializes the UART FIFO.
 *
 * This function initializes a First In, First Out (FIFO) for use with the UART.
 *
 * @param fifo Pointer to the UART FIFO to be initialized.
 */
void UART.{port}._init_fifo(UART_FIFO *fifo);

/**
 * @brief Pushes data into the UART FIFO.
 *
 * This function pushes a byte of data into the UART FIFO.
 *
 * @param fifo Pointer to the UART FIFO where the data will be pushed.
 * @param data The byte of data to be pushed into the FIFO.
 */
void UART.{port}._push(UART_FIFO *fifo, char data);

/**
 * @brief Pops data from the UART FIFO.
 *
 * This function pops a byte of data from the UART FIFO.
 *
 * @param fifo Pointer to the UART FIFO from which the data will be popped.
 * @return The byte of data popped from the FIFO.
 */
char UART.{port}._pop(UART_FIFO *fifo);

/**
 * @brief Peeks at the last received value in the UART input FIFO.
 *
 * This function retrieves the last received value from the UART input FIFO
 * without removing it from the FIFO.
 *
 * @return The last received value in the UART input FIFO.
 */
char UART.{port}._peek(UART_FIFO *fifo);

/**
 * @brief Configures UART for simplex mode.
 *
 * This function configures the UART for simplex mode by setting the necessary
 * control bits in the UART registers.
 */
void UART.{port}._simplexMode(void);

/**
 * @brief Configures UART flow control.
 *
 * This function configures UART flow control based on the provided parameter.
 *
 * @param enabled Flag indicating whether flow control is enabled (1) or disabled (0).
 */
void UART.{port}._flowControl(uint8_t enabled);

/**
 * @brief Inverts UART signals.
 *
 * This function inverts UART signals based on the provided parameter.
 *
 * @param invert Flag indicating whether to invert UART signals (1) or not (0).
 */
void UART.{port}._invert(uint8_t invert);

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
void UART.{port}._bd(uint32_t uartSpeed);

/**
 * @brief Initializes the UART module.
 *
 * This function initializes the UART module, configuring input and output functions,
 * setting the baud rate, and enabling the module for communication.
 */
void UART.{port}._init(void);

/**
 * @brief Turns off the UART module.
 *
 * This function turns off the UART module by disabling UARTEN and UTXEN, and
 * also disables RX and TX interrupts.
 */
void UART.{port}._OFF(void);

/**
 * @brief Turns on the UART module.
 *
 * This function turns on the UART module by enabling UARTEN and UTXEN, and
 * also enables RX and TX interrupts. Additionally, it initializes the input
 * and output FIFO buffers.
 */
void UART.{port}._ON(void);

char UART.{port}._IN_pop(void);

uint16_t UART.{port}._IN_count(void);

void UART.{port}._OUT_push(char d);

uint16_t UART.{port}._OUT_count(void);

extern const streamIn_t  streamIn_Uart.{port}.;
extern const streamOut_t streamOut_Uart.{port}.;

/*==================[external functions definition]==========================*/

/**
 * @brief External callback function for UART receive interrupt.
 *
 * This function serves as an external callback for the UART receive interrupt.
 * When defined, it is invoked within the UART receive interrupt service routine (ISR)
 * to handle received data. Users can implement their own custom logic for data processing
 * by providing a callback function that conforms to the signature:
 * \code
 * extern void ISR_UART.{port}._CALLBACK(char d);
 * \endcode
 *
 * @param d The received character/data passed to the callback function.
 *
 * @note Users should define their custom callback function with the specified signature
 * to handle the received data within the context of the UART receive ISR.
 * The actual behavior of the callback is determined by the user's implementation.
 * To enable the callback, it should be defined and associated with the corresponding UART receive ISR.
 */
EMIC:ifdef(UART.{port}._CALLBACK_RX)
extern void ISR_UART.{port}._CALLBACK(char d);
EMIC:endif
#endif 