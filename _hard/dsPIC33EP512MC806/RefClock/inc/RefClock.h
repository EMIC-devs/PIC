/*************************************************************************//**
  @file     RefClock.h

  @brief    Driver Library to use Reference clock generator

  @author   Rottoli Luciano

  @date     20/07/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/
#ifndef _REFCLOCK_H_
#define _REFCLOCK_H_
/*==================[inclusions]=============================================*/
#include <xc.h>

/*==================[typedefs]===============================================*/
// Enumeration for reference clock dividers with corresponding RODIV values
typedef enum {
    REFCLK_DIV1 = 0x0000,   // Reference clock
    REFCLK_DIV2 = 0x0001,   // Reference clock divided by 2
    REFCLK_DIV4 = 0x0002,   // Reference clock divided by 4
    REFCLK_DIV8 = 0x0003,   // Reference clock divided by 8
    REFCLK_DIV16 = 0x0004,  // Reference clock divided by 16
    REFCLK_DIV32 = 0x0005,  // Reference clock divided by 32
    REFCLK_DIV64 = 0x0006,  // Reference clock divided by 64
    REFCLK_DIV128 = 0x0007, // Reference clock divided by 128
    REFCLK_DIV256 = 0x0008, // Reference clock divided by 256
    REFCLK_DIV512 = 0x0009, // Reference clock divided by 512
    REFCLK_DIV1024 = 0x000A, // Reference clock divided by 1024
    REFCLK_DIV2048 = 0x000B, // Reference clock divided by 2048
    REFCLK_DIV4096 = 0x000C, // Reference clock divided by 4096
    REFCLK_DIV8192 = 0x000D, // Reference clock divided by 8192
    REFCLK_DIV16384 = 0x000E, // Reference clock divided by 16384
    REFCLK_DIV32768 = 0x000F  // Reference clock divided by 32768
} RefCLK_Div;

/*==================[external data declaration]==============================*/
/* None */

/*==================[external functions declaration]=========================*/

/** 
 * @brief Initializes the reference clock by configuring the appropriate pin 
 *        and setting up the PPS.
 */
void init_RefCLK(void);

/**
 * @brief Sets the reference clock divider.
 * 
 * @param Div The desired divider from the RefCLK_Div enumeration.
 */
void RefCLK_setDiv(RefCLK_Div Div);

/**
 * @brief Turns the reference oscillator on or off.
 * 
 * @param powerOn Pass 1 to turn on the reference oscillator, 0 to turn it off.
 */
void RefCLK_SetPower(uint8_t powerOn);

/**
 * @brief Enables or disables the reference oscillator in sleep mode.
 * 
 * @param enable Pass 1 to enable the oscillator in sleep mode, 0 to disable it.
 */
void RefCLK_SetSleepMode(uint8_t enable);

/**
 * @brief Selects the reference oscillator source.
 * 
 * @param useCrystal Pass 1 to use the oscillator crystal, 0 to use the system clock.
 */
void RefCLK_SetSource(uint8_t useCrystal);



/*==================[end of file]============================================*/
#endif // _REFCLOCK_H_
