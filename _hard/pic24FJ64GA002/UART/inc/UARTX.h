/*************************************************************************//**
  @file     UARTX.c

  @brief    Hardware Library to use UART

  @author   Rottoli Luciano

  @version  v0.0.1  

  @date		01/03/2024    

 ******************************************************************************/
#ifndef _UART.{port}._H_
#define _UART.{port}._H_

#include "inc/streamIn.h"
#include "inc/streamOut.h"
/*==================[macros and definitions]=================================*/
#define UART.{port}._MAX_BUFFER_SIZE .{BufferSize}.

typedef struct {
    char buffer[UART.{port}._MAX_BUFFER_SIZE];
    uint16_t start;      // Pointer to the start of the queue
    uint16_t end;        // Pointer to the end of the queue
    uint16_t count;      // Count of data elements in the queue
} UART_FIFO;

/*==================[external data definition]===============================*/
uint8_t     UART.{port}._flowControlVar = 0;
uint8_t     UART.{port}._inverted       = 0;

/*==================[public functions definition]==========================*/

uint16_t UART.{port}._count(const UART_FIFO *fifo);
uint16_t UART.{port}._is_empty(const UART_FIFO *fifo);
uint8_t UART.{port}._is_full(const UART_FIFO *fifo);
void UART.{port}._init_fifo(const UART_FIFO *fifo);
void UART.{port}._push(const UART_FIFO *fifo, char data);
char UART.{port}._pop(const UART_FIFO *fifo);
char UART.{port}._peek(const UART_FIFO *fifo);
void UART.{port}._simplexMode(void);
void UART.{port}._flowControl(uint8_t enabled);
void UART.{port}._invert(uint8_t invert);
void UART.{port}._bd(uint32_t uartSpeed);
void UART.{port}._init(void);
void UART.{port}._OFF(void);
void UART.{port}._ON(void);

void UART.{port}._Poll(void);
EMIC:define(polls.UART.{port}._Poll,UART.{port}._Poll)

char UART.{port}._IN_pop(void);

uint16_t UART.{port}._IN_count(void);

void UART.{port}._OUT_push(char d);

uint16_t UART.{port}._OUT_count(void);

const streamIn_t  streamIn_Uart.{port}.  = {UART.{port}._IN_pop, UART.{port}._IN_count};
const streamOut_t streamOut_Uart.{port}. = {UART.{port}._OUT_push, UART.{port}._OUT_count};

#endif 