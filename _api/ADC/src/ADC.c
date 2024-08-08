/*************************************************************************//**
  @file     ADC.c

  @brief    API Library to use LTC 2500 ADC

  @author   Rottoli Luciano

  @date     10/07/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include "inc/ADC.h"
#include "inc/LTC2500.h"
#include "inc/RefClock.h"

uint8_t ADC_Started = 0;
uint32_t ADC_Counter = 0;
uint32_t ADC_Quantity = 0;

void init_ADC(void)
{
    LTC2500_init();
    init_RefCLK();
    RefCLK_setDiv(REFCLK_DIV64);
    LTC2500Config.bits.c11 = 1;
    LTC2500Config.bits.c10 = 0;
    SET_FILTER_TYPE_AVERAGING(LTC2500Config);
    SET_DF_4(LTC2500Config);
    SET_DGE_OFF(LTC2500Config);
    SET_DGC_OFF(LTC2500Config);
    LTC2500_SendConfig();
}

void start_ADC(uint8_t Freq, uint32_t Quantity)
{
    ADC_Started = 1;
    ADC_Quantity = Quantity;

    LTC2500Config.bits.c11 = 1;
    LTC2500Config.bits.c10 = 0;
    SET_FILTER_TYPE_AVERAGING(LTC2500Config);
    SET_DGE_OFF(LTC2500Config);
    SET_DGC_OFF(LTC2500Config);
    switch (Freq)
    {
    case 1:
        SET_DF_4(LTC2500Config);
        break;
    case 2:
        SET_DF_8(LTC2500Config);
        break;
    case 3:
        SET_DF_16(LTC2500Config);
        break;
    case 4:
        SET_DF_32(LTC2500Config);
        break;
    case 5:
        SET_DF_64(LTC2500Config);
        break;
    case 6:
        SET_DF_128(LTC2500Config);
        break;
    case 7:
        SET_DF_256(LTC2500Config);
        break;
    case 8:
        SET_DF_512(LTC2500Config);
        break;
    case 9:
        SET_DF_1024(LTC2500Config);
        break;
    case 10:
        SET_DF_2048(LTC2500Config);
        break;
    case 11:
        SET_DF_4096(LTC2500Config);
        break;
    case 12:
        SET_DF_8192(LTC2500Config);
        break;
    case 13:
        SET_DF_16384(LTC2500Config);
        break;
    default:
        SET_DF_4(LTC2500Config);
        break;
    }
    LTC2500_SendConfig();
    RefCLK_SetPower(1);
}

void poll_ADC(void)
{
    if(ADC_Started)
    {
        if(ADC_Counter >= ADC_Quantity)
        {
            RefCLK_SetPower(0);
            ADC_Started = 0;
            ADC_Counter = 0;
            EMIC:ifdef event_eADCEnd_active
            eADCEnd();
            EMIC:endif
        }
        if(LTC2500_DRLStatus())
        {
            ADC_Counter ++;
            LTC2500Result ADC_result;
            ADC_result = LTC2500_readFiltered();
            EMIC:ifdef event_eADC_active
            eADC(&ADC_result.data);
            EMIC:endif
        }
    }
}
