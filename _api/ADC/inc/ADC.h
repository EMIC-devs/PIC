/*************************************************************************//**
  @file     ADC.h

  @brief    API Library to use LTC 2500 ADC - Header File

  @details  This file contains the function declarations for using the LTC2500 ADC.

  @date     10/07/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

#ifndef ADC_H
#define ADC_H

/*==================[inclusions]=============================================*/
#include <xc.h>
#include <stdint.h>


/*==================[external functions declaration]=========================*/
/**
 * @brief Initializes the ADC.
 *
 * This function initializes the LTC2500 ADC and the reference clock.
 */
void init_ADC(void);
EMIC:define(inits.init_ADC,init_ADC)

/**
 * @brief Starts the ADC conversion process.
 *
 * @param Freq The decimation factor to set.
 * @param Quantity The number of samples to acquire.
 */
void start_ADC(uint8_t Freq, uint32_t Quantity);

/**
 * @brief Polls the ADC for new data.
 *
 * This function should be called periodically to check if new data is available
 * from the ADC and process it accordingly.
 */
void poll_ADC(void);
EMIC:define(polls.poll_ADC,poll_ADC)


#endif /* ADC_H */
