/*************************************************************************//**
  @file     pwm.c

  @brief    Hardware Library to use PWM

  @author   Francisco Martinez

  @version  v0.0.1  

  @date		02/07/2024  
 ******************************************************************************/
#include <string.h>
#include <math.h>
#include "inc/pwm.{pwm_generator_number}..h"
#include "inc/system.h"

/*==================[public variables definition]==========================*/

//Variable used to save the PTPER Register value. It changes the frequency of the pwm (Fpwm)
uint16_t PTPER_Register.{pwm_generator_number}. = 0; //Fpwm = Fosc / (Prescaler * (PTPER+1))

//Variable used to save the PDC Register value. It changes the duty cycle of the pwm
uint16_t PDC_Register.{pwm_generator_number}. = 0; //PDC = (PTPER +1 * Duty)/100 

//Variable used to save the Prescaler value. It changes the frequency of the pwm (Fpwm)
uint16_t Prescaler_Register.{pwm_generator_number}. = 0; //Fpwm = Fosc / (Prescaler * (PTPER+1))

//Variable used to save the PWM duty cycle value
float Duty_Cycle.{pwm_generator_number}. = 0;

//Variable used to save the PWM frequency value
uint32_t Freq.{pwm_generator_number}. = 0;

void pwm.{pwm_generator_number}._init(void)
{
  PTCONbits.PTEN = 0; //Disable the PWM Outputs
  PTCONbits.PTSIDL = 0; //PWM time base runs in CPU Idle mode          
  PTCON2bits.PCLKDIV = 0b000; //Set the prescaler to 1:1     
  PWMCON.{pwm_generator_number}.bits.MDCS = 0; //PDCx and SDCx registers provide duty cycle information for this PWM generator
  PWMCON.{pwm_generator_number}.bits.MTBS = 0; //PWM generator uses the primary master time base for synchronization and as the clock source for the PWM generation logic
  IOCON.{pwm_generator_number}.bits.PMOD = 0b00; //PWM I/O pin pair is in the Complementary Output mode

  PTCONbits.SESTAT = 0; // Clear the Special event interrupt Flag
  PTCONbits.SEVTPS = 0; // Special Event Trigger output postscaler set to 1:1 selection
  PTCONbits.SEIEN = 0; // Special event interrupt is enabled

  if(!strcmp(".{PWMH_State}.","ON"))
  {
    IOCON.{pwm_generator_number}.bits.PENH = 1; //PWM module controls PWMxH pin
  }
  else if(!strcmp(".{PWMH_State}.","OFF"))
  {
    IOCON.{pwm_generator_number}.bits.PENH = 0; //Digital I/O module controls PWMxH pin
  }

  if(!strcmp(".{PWML_State}.","ON"))
  {
    IOCON.{pwm_generator_number}.bits.PENL = 1; //PWM module controls PWMxL pin
  }
  else if(!strcmp(".{PWML_State}.","OFF"))
  {
    IOCON.{pwm_generator_number}.bits.PENL = 0; //Digital I/O module controls PWMxL pin
  }
}

void pwm.{pwm_generator_number}._start(void)
{
  //change PTEN register
  PTCONbits.PTEN = 1;
}

void pwm.{pwm_generator_number}._stop(void)
{
  //change PTEN register
  PTCONbits.PTEN = 0;
}

void pwm.{pwm_generator_number}._set_duty(float duty)
{
  Duty_Cycle.{pwm_generator_number}. = duty;
  if(Freq.{pwm_generator_number}. != 0)
  {
    //calculate the value of PDC according to the pwm frequency
    float cal = PTPER_Register.{pwm_generator_number}. + 1;
    cal = cal * duty;
    cal = cal / 100;
    PDC_Register.{pwm_generator_number}. = (uint16_t)round(cal); //PDC = ((PTPER +1) * Duty)/100        
  }
  else
  {
    PDC_Register.{pwm_generator_number}. = 0;
  }
  
  //change PDC register
  PDC.{pwm_generator_number}. = PDC_Register.{pwm_generator_number}.;
}

void pwm.{pwm_generator_number}._set_frequency(uint32_t frequency)
{
  Freq.{pwm_generator_number}. = frequency;
  if(Freq.{pwm_generator_number}. != 0)
  {
    //calculate the value of PTPER according to the pwm frequency
    PTPER_Register.{pwm_generator_number}. = (uint32_t)round(FOSC/(frequency * Prescaler_Register.{pwm_generator_number}.)); //Fpwm = Fosc / (Prescaler * PTPER)
  }
  else
  {
    PTPER_Register.{pwm_generator_number}. = 0;
  }
    //change PTPER register
    PTPER = PTPER_Register.{pwm_generator_number}.;

    //calculate the duty cycle so that it remains constant even if the frequency changes
    pwm.{pwm_generator_number}._set_duty(Duty_Cycle.{pwm_generator_number}.);

}

void pwm.{pwm_generator_number}._set_prescaler(uint8_t prescaler)
{

  switch(prescaler)
  {
    case 1:
      //change prescaler variable
      Prescaler_Register.{pwm_generator_number}. = 1;
      //change prescaler register
      PTCON2bits.PCLKDIV = 0b000;
      break;
    case 2:
      Prescaler_Register.{pwm_generator_number}. = 2;
      PTCON2bits.PCLKDIV = 0b001;
      break;
    case 4:
      Prescaler_Register.{pwm_generator_number}. = 4;
      PTCON2bits.PCLKDIV = 0b010;
      break;
    case 8:
      Prescaler_Register.{pwm_generator_number}. = 8;
      PTCON2bits.PCLKDIV = 0b011;
      break;
    case 16:
      Prescaler_Register.{pwm_generator_number}. = 16;
      PTCON2bits.PCLKDIV = 0b100;
      break;
    case 32:
      Prescaler_Register.{pwm_generator_number}. = 32;
      PTCON2bits.PCLKDIV = 0b101;
      break;
    case 64:
      Prescaler_Register.{pwm_generator_number}. = 64;
      PTCON2bits.PCLKDIV = 0b110;
      break;
    default:
      break;
  }
  //calculate the frequency so that it remains constant even if the prescaler changes
  pwm.{pwm_generator_number}._set_frequency(Freq.{pwm_generator_number}.);

}

void pwm.{pwm_generator_number}._set_interrupt(void)
{ 
  PTCONbits.SEIEN = 1;       // Set PWM Interrupt
}

void pwm.{pwm_generator_number}._unset_interrupt(void)
{ 
  PTCONbits.SEIEN = 0;       // Unset PWM Interrupt
}

void pwm.{pwm_generator_number}._clear_interrupt_flag(void)
{
  PTCONbits.SESTAT = 0;      // Clear the Special event interrupt Flag
}