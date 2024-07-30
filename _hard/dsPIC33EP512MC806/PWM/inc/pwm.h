/*************************************************************************//**
  @file     pwm.h

  @brief    Hardware Library to use PWM

  @author   Francisco Martinez

  @version  v0.0.1  

  @date		02/07/2024  
 ******************************************************************************/

#ifndef PIC_pwm.{pwm_generator_number}._H_
#define PIC_pwm.{pwm_generator_number}._H_

/*==================[inclusions]=============================================*/
#include <xc.h>

/*==================[public functions definition]==========================*/

/**
 * @brief Initializes the PWM module.
 */
void pwm.{pwm_generator_number}._init(void);

/**
 * @brief Enable the PWM Output.
 *
 */
void pwm.{pwm_generator_number}._start(void);

/**
 * @brief Disable the PWM Output.
 *
 */
void pwm.{pwm_generator_number}._stop(void);

/**
 * @brief Set the duty parameter for the PWM Output.
 *
 * @param duty The desired duty cicle for PWM Output.
 */
void pwm.{pwm_generator_number}._set_duty(float duty);

/**
 * @brief Set the frequency parameter for the PWM Output.
 *
 * @param frequency The desired frequency for PWM Output.
 */
void pwm.{pwm_generator_number}._set_frequency(uint32_t frequency);

/**
 * @brief Set the prescaler parameter for the PWM Output.
 *
 * @param prescaler The desired prescaler for PWM Output.
 */
void pwm.{pwm_generator_number}._set_prescaler(uint8_t prescaler);

/**
 * @brief Enable PWM cycle start interrupt.
 */
void pwm.{pwm_generator_number}._set_interrupt(void);

/**
 * @brief Disable PWM cycle start interrupt.
 */
void pwm.{pwm_generator_number}._unset_interrupt(void);

/**
 * @brief Clear PWM cycle start interrupt flag.
 */
void pwm.{pwm_generator_number}._clear_interrupt_flag(void);

/*==================[end of file]============================================*/
#endif //PIC_pwm.{pwm_generator_number}._H_