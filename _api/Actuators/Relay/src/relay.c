/*****************************************************************************
  @file     Rele.c

  @brief    API Library to use RELE

  @author   Pentacolo Tomas (based on PL)

  @date     08/06/2023

  @version  1.0.0 - Initial release.
 ******************************************************************************/
#include <xc.h>
#include "inc/relay_.{name}..h"
#include "inc/gpio.h"

EMIC:ifdef(usedFunction.relay_.{name}.)

void initRelay_.{name}.(void)
{
    HAL_GPIO_PinCfg(.{pin}., GPIO_OUTPUT);
    HAL_GPIO_PinSet(.{pin}., GPIO_LOW);
}


void relay_.{name}.(uint8_t stateRelay)
{
	switch (stateRelay)
    {
    case 0:
        HAL_GPIO_PinSet(.{pin}., GPIO_LOW);
        break;
    case 1:
        HAL_GPIO_PinSet(.{pin}., GPIO_HIGH);
        break;
    case 2:
        HAL_GPIO_PinSet(.{pin}., !HAL_GPIO_PinGet(.{pin}.));
        break;
    default:
        break;
    }
}
EMIC:endif

