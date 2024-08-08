/*************************************************************************//**
  @file     RefClock.c

  @brief    Driver Library to use Reference clock generator

  @author   Rottoli Luciano

  @date     20/07/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "inc/gpio.h"
#include "inc/RefClock.h"

// Function to initialize the reference clock
void init_RefCLK(void)
{
    HAL_GPIO_PinCfg(.{PinName}., GPIO_OUTPUT);  // Configure the pin as output

    __builtin_write_OSCCONL(OSCCON & 0xbf); // Unlock PPS

    RPOUT_.{PinName}. = _RPOUT_REFCLK;          // Set the pin for reference clock output

    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS
}

// Function to set the reference clock divider
void RefCLK_setDiv(RefCLK_Div Div)
{
    uint8_t WasOn = 0;
    if (_ROON)  // Check if the reference clock is on
    {
        WasOn = 1;
        _ROON = 0;  // Turn off the reference clock
    }

    // Validate the Div value before assignment
    switch (Div) {
        case REFCLK_DIV1:
        case REFCLK_DIV2:
        case REFCLK_DIV4:
        case REFCLK_DIV8:
        case REFCLK_DIV16:
        case REFCLK_DIV32:
        case REFCLK_DIV64:
        case REFCLK_DIV128:
        case REFCLK_DIV256:
        case REFCLK_DIV512:
        case REFCLK_DIV1024:
        case REFCLK_DIV2048:
        case REFCLK_DIV4096:
        case REFCLK_DIV8192:
        case REFCLK_DIV16384:
        case REFCLK_DIV32768:
            _RODIV = Div; // Valid value, assign it
            break;
        default:
            _RODIV = REFCLK_DIV1; // Default value in case of error
            // Optionally, handle error here (e.g., log it, return an error code, etc.)
            break;
    }

    if (WasOn)  // If the reference clock was on, turn it back on
    {
        _ROON = 1;
    }
}

// Function to turn the reference oscillator on or off
void RefCLK_SetPower(uint8_t powerOn)
{
    _ROON = powerOn;
}

// Function to enable or disable the reference oscillator in sleep mode
void RefCLK_SetSleepMode(uint8_t enable)
{
    _ROSSLP = enable;  // Assign the value directly to the ROSSLP bit
}

// Function to select the reference oscillator source
void RefCLK_SetSource(uint8_t useCrystal)
{
    _ROSEL = useCrystal;  // Assign the value directly to the ROSEL bit
}
