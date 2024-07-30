/*************************************************************************//**
  @file     ecometer.c

  @brief    API Library to use Ecometer

  @authors  Francisco Martinez, Ramiro Alarcon, Luciano Rottoli

  @version  v0.0.1  

  @date		04/07/2024  
 ******************************************************************************/
#include "inc/pwm.{pwm_generator_number}..h"
#include "inc/ecometer.{pwm_generator_number}..h"

void PWM.{pwm_generator_number}._Init(void)
{
    pwm.{pwm_generator_number}._init();
}

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._Start
void PWM.{pwm_generator_number}._Start(void)
{
    pwm.{pwm_generator_number}._start();
}
EMIC:endif

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._Stop
void PWM.{pwm_generator_number}._Stop(void)
{
    pwm.{pwm_generator_number}._stop();
}
EMIC:endif

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._set_frequency
void PWM.{pwm_generator_number}._set_frequency(uint32_t frequency)
{
    pwm.{pwm_generator_number}._set_frequency(frequency);
}
EMIC:endif

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._set_duty
void PWM.{pwm_generator_number}._set_duty(uint8_t duty)
{
    pwm.{pwm_generator_number}._set_duty(duty);
}
EMIC:endif

EMIC:ifdef usedFunction.PWM.{pwm_generator_number}._set_prescaler
void PWM.{pwm_generator_number}._set_prescaler(uint8_t prescaler)
{
    pwm.{pwm_generator_number}._set_prescaler(prescaler);
}
EMIC:endif