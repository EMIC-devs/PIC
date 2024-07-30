/*************************************************************************//**
  @file     pwm.c

  @brief    API library to produce a variable tone based on an initial frequency,
            a frequency transition step and a number of periods to be produced

  @author   Francisco Martinez

  @version  v0.0.1  

  @date		04/07/2024  
 ******************************************************************************/
#include <math.h>
#include "inc/system.h"
#include "inc/pwm.{pwm_generator_number}..h"
#include "inc/tones.{tone_number}..h"
#include "inc/gpio.h"

#define PI 3.1415926
#define pwm_frequency 16000
#define pwm_prescaler 1

/*==================[public variables definition]==========================*/

uint16_t PTPER_Range = FOSC/(pwm_frequency * pwm_prescaler);
uint32_t tone_frequency;
uint32_t tone_step;
uint32_t tone_periods_number;
float tone_phase;
float tone_duty;
void Tone.{tone_number}._init(void)
{
    pwm.{pwm_generator_number}._init();
}

EMIC:ifdef usedFunction.Tone.{tone_number}._play_tone
void Tone.{tone_number}._play_tone(uint32_t initial_frequency, uint32_t step, uint32_t periods_number)
{
    IOCON.{pwm_generator_number}.bits.POLL = 0;
    pwm.{pwm_generator_number}._set_prescaler(pwm_prescaler);
    pwm.{pwm_generator_number}._set_frequency(pwm_frequency);
    HAL_GPIO_PinCfg(POT_PWM_INH, GPIO_OUTPUT);
    HAL_GPIO_PinSet(POT_PWM_INH, GPIO_LOW);
    tone_frequency = initial_frequency;
    tone_step = step;
    tone_periods_number = periods_number;
    tone_phase = 0;
    pwm.{pwm_generator_number}._start();
    pwm.{pwm_generator_number}._set_interrupt();
    HAL_GPIO_PinSet(POT_PWM_INH, GPIO_HIGH);
}
EMIC:endif

void Tone.{tone_number}._poll(void)
{
    if(PTCONbits.SESTAT == 1)
    {
        if (tone_phase <(float)((float)1 / (float)tone_frequency))
        {
            tone_phase = roundf(tone_phase * 10000) / 10000; //Redondeo a 4 decimales
            tone_duty = 50 + 50 * sin(2 * PI * tone_frequency * tone_phase); //Transformamos la amplitud de la senoidal, segun el valor de su fase a un porcentaje de 0% a 100%
            pwm2_set_duty(tone_duty);
            tone_phase += (float)1 / pwm_frequency; //tone_phase = (2 PI) / PTPER_Range
            PTCONbits.SESTAT = 0;
        }
        else
        {
            tone_phase = 0;
            if (tone_periods_number > 0)
            {
                tone_frequency += tone_step;
                tone_periods_number--;
                if (tone_periods_number == 0)
                {
                    pwm2_stop();
                }
            }
        } 
    }   
}
