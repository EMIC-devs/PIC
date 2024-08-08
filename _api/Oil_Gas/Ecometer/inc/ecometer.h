/*************************************************************************//**
  @file     ecometer.h

  @brief    API Library to use Ecometer

  @authors  Francisco Martinez, Ramiro Alarcon, Luciano Rottoli

  @version  v0.0.1  

  @date		04/07/2024  
 ******************************************************************************/

#ifndef __ECOMETER_.{pwm_generator_number}._H__
#define __ECOMETER_.{pwm_generator_number}._H__

#include <xc.h>

void PWM.{pwm_generator_number}._Init();
EMIC:define(inits.PWM.{pwm_generator_number}._Init,PWM.{pwm_generator_number}._Init)

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._Start
void PWM.{pwm_generator_number}._Start();
EMIC:endif

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._Stop
void PWM.{pwm_generator_number}._Stop();
EMIC:endif

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._set_frequency
void PWM.{pwm_generator_number}._set_frequency(uint32_t frequency);
EMIC:endif

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._set_duty
void PWM.{pwm_generator_number}._set_duty(uint8_t duty);
EMIC:endif

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._set_prescaler
void PWM.{pwm_generator_number}._set_prescaler(uint8_t prescaler);
EMIC:endif


#endif