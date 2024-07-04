/*************************************************************************//**
  @file     pwm.h

  @brief    Hardware Library to use PWM

  @author   Francisco Martinez

  @version  v0.0.1  

  @date		02/07/2024  
 ******************************************************************************/

#ifndef PIC_pwm_H_
#define PIC_pwm_H_

/*==================[inclusions]=============================================*/

#include <xc.h>
#include <math.h>
/*==================[external data declaration]==============================*/

/*==================[public variables definition]==========================*/

//Variable used to save the PTPER Register value. It changes the frequency of the pwm (Fpwm)
uint16_t PTPER_Register = 0; //Fpwm = Fosc / (Prescaler * (PTPER+1))

//Variable used to save the PDC Register value. It changes the duty cycle of the pwm
uint16_t PDC_Register = 0; //PDC = (PTPER +1 * Duty)/100 

//Variable used to save the Prescaler value. It changes the frequency of the pwm (Fpwm)
uint16_t Prescaler_Register = 0; //Fpwm = Fosc / (Prescaler * (PTPER+1))

//Variable used to save the PWM duty cycle value
uint8_t Duty_Cycle = 0;

//Variable used to save the PWM frequency value
uint32_t Freq = 0;

//Variable used to save the PWM state (if it?s running or not)
enum PWM_State
{
	PWM_ON,
	PWM_OFF
};

/*==================[public functions definition]==========================*/

/**
 * @brief Initializes the PWM module.
 *
 * This function initializes the PWM module, configuring .
 */
void pwm.{pwm_generator_number}._init(void);

/**
 * @brief Enable the PWM Output.
 *
 * This function start the PWM Output.
 *
 */
void pwm.{pwm_generator_number}._start(void);

/**
 * @brief Disable the PWM Output.
 *
 * This function stop the PWM Output.
 *
 */
void pwm.{pwm_generator_number}._stop(void);

/**
 * @brief Set the duty parameter for the PWM Output.
 *
 * This function change the PWM duty cycle.
 *
 * @param duty The desired duty cicle for PWM Output.
 */
void pwm.{pwm_generator_number}._set_duty(uint8_t duty);

/**
 * @brief Set the frequency parameter for the PWM Output.
 *
 * This function change the PWM frequency.
 *
 * @param frequency The desired frequency for PWM Output.
 */
void pwm.{pwm_generator_number}._set_frequency(uint32_t frequency);

/**
 * @brief Set the prescaler parameter for the PWM Output.
 *
 * This function change the PWM prescaler.
 *
 * @param prescaler The desired prescaler for PWM Output.
 */
void pwm.{pwm_generator_number}._set_prescaler(uint8_t prescaler);
/*==================[end of file]============================================*/
#endif