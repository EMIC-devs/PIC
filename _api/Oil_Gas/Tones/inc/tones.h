/*************************************************************************//**
  @file     tones.h

  @brief    API library to produce a variable tone based on an initial frequency,
            a frequency transition step and a number of periods to be produced

  @authors  Francisco Martinez

  @version  v0.0.1  

  @date		04/07/2024  
 ******************************************************************************/
#include <xc.h>

#ifndef __TONES_.{tone_number}._H__
#define __TONES_.{tone_number}._H__

/**
 * @brief Initializes the PWM module.
 */
void Tone.{tone_number}._init(void);
EMIC:define(inits.Tone.{tone_number}._init,Tone.{tone_number}._init)

/**
 * @brief Play Output Tone
 *
 * @param initial_frequency The initial frequency for the Output Tone.
 * 
 * @param step The frequency step from the initial frequency for the Output Tone.
 * 
 * @param periods_number The cycles or periods number for the Output Tone.
 */
EMIC:ifdef usedFunction.Tone.{tone_number}._play_tone
void Tone.{tone_number}._play_tone(uint32_t initial_frequency, uint32_t step, uint32_t periods_number);
EMIC:endif

/**
 * @brief Calculate the duty cycle value of the next pwm cycle.
 */
void Tone.{tone_number}._poll(void);
EMIC:define(polls.Tone.{tone_number}._poll,Tone.{tone_number}._poll)
#endif