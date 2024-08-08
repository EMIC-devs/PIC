/*************************************************************************//**
  @file     LTC2500.c

  @brief    Driver Library to use LTC 2500 ADC

  @author   Rottoli Luciano

  @date     10/07/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "inc/gpio.h"
#include "inc/LTC2500.h"

union LT2500_32_CONTW LTC2500Config;

void LTC2500_init(void)
{
    HAL_GPIO_PinCfg(ADC_Busy,GPIO_INPUT);
    HAL_GPIO_PinCfg(ADC_DRL,GPIO_INPUT);
    HAL_GPIO_PinCfg(ADC_RDLa,GPIO_OUTPUT);
    HAL_GPIO_PinCfg(ADC_RDLb,GPIO_OUTPUT);
    HAL_GPIO_PinCfg(ADC_PRE,GPIO_OUTPUT);
    HAL_GPIO_PinCfg(ADC_MCLK,GPIO_OUTPUT);
    HAL_GPIO_PinCfg(ADC_SYNC,GPIO_OUTPUT);
    HAL_GPIO_PinCfg(ADC_A_MOSI, GPIO_OUTPUT);
	HAL_GPIO_PinCfg(ADC_A_SCLK, GPIO_OUTPUT);
    HAL_GPIO_PinCfg(ADC_A_MISO, GPIO_INPUT);

    HAL_GPIO_PinSet(ADC_RDLa,GPIO_LOW);
    HAL_GPIO_PinSet(ADC_RDLb,GPIO_HIGH);
    HAL_GPIO_PinSet(ADC_PRE,GPIO_LOW);
    HAL_GPIO_PinSet(ADC_SYNC,GPIO_LOW);
    HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_LOW); // Ensure clock is low initially

}


LTC2500Result LTC2500_readFiltered(void)
{
    LTC2500Result result = {0};
    uint8_t i;

    // while (!HAL_GPIO_PinGet(ADC_DRL)); // Wait for DRL to go high
    // while (HAL_GPIO_PinGet(ADC_DRL));  // Wait for DRL to go low

    for (i = 0; i < 32; i++) {
        HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_HIGH);
        if (HAL_GPIO_PinGet(ADC_A_MISO)) {
            result.data |= (1 << (31 - i));
        }
        HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_LOW);
    }

    for (i = 0; i < 4; i++) {
        HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_HIGH);
        if (HAL_GPIO_PinGet(ADC_A_MISO)) {
            result.config.downsampling_factor |= (1 << (3 - i));
        }
        HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_LOW);
    }
    for (i = 0; i < 4; i++) {
        HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_HIGH);
        if (HAL_GPIO_PinGet(ADC_A_MISO)) {
            result.config.filter_type |= (1 << (3 - i));
        }
        HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_LOW);
    }

    return result;
}

void LTC2500_SendConfig(void)
{
     LTC2500_StartConv();

    // Wait for DRL to go high, then low
    while (!LTC2500_DRLStatus());
    while (LTC2500_DRLStatus());

    // Send the 12-bit value in the specified order (from bit 15 to 4)
    uint8_t i;
    for (i = 15; i > 3; i--) {
        HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_HIGH);
        if (LTC2500Config.all_bits & (1 << i)) {
            HAL_GPIO_PinSet(ADC_A_MOSI, GPIO_HIGH);
        } else {
            HAL_GPIO_PinSet(ADC_A_MOSI, GPIO_LOW);
        }
        HAL_GPIO_PinSet(ADC_A_SCLK, GPIO_LOW);
    }
}

void LTC2500_StartConv(void)
{
    HAL_GPIO_PinSet(ADC_MCLK,GPIO_HIGH);
    Nop();
    HAL_GPIO_PinSet(ADC_MCLK,GPIO_LOW);
}

uint8_t LTC2500_DRLStatus(void)
{
    return HAL_GPIO_PinGet(ADC_DRL);
}