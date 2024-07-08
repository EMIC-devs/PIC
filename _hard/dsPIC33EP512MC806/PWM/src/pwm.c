/*************************************************************************//**
  @file     pwm.c

  @brief    Hardware Library to use PWM

  @author   Francisco Martinez

  @version  v0.0.1  

  @date		02/07/2024  
 ******************************************************************************/

#define FOSC 46062500  //46.062500 MHz

void pwm.{pwm_generator_number}._init(void)
{
  PTCONbits.PTEN = 0; //Disable the PWM Outputs
  PTCONbits.PTSIDL = 0; //PWM time base runs in CPU Idle mode            
  PTCON2bits.PCLKDIV = 0b000; //Set the prescaler to 1:1                    
  PWMCON.{pwm_generator_number}.bits.PMOD = 0b00; //PWM I/O pin pair is in the Complementary Output mode
  PWMCON.{pwm_generator_number}.bits.PENH = 1; //PWM module controls PWMxH pin
  PWMCON.{pwm_generator_number}.bits.PENL = 1; //PWM module controls PWMxL pin
}

void pwm.{pwm_generator_number}._start(void)
{
  //change PTEN register
  PTCONbits.PTEN = 1;
  PWM_State = PWM_ON;
}

void pwm.{pwm_generator_number}._stop(void)
{
  //change PTEN register
  PTCONbits.PTEN = 0;
  PWM_State = PWM_OFF;
}

void pwm.{pwm_generator_number}._set_duty(uint8_t duty)
{
  bool State = PWM_State;
  //Stop the PWM if it is active
  if(State)
  {
    pwm.{pwm_generator_number}._stop()
  }

  Duty_Cycle = duty;
  //calculate the value of PDC according to the pwm frequency
  PDC_Register = (uint16_t)round(((PTPER_Register + 1) * duty) / 100); //PDC = (PTPER +1 * Duty)/100

  //change PDC register
  PDC.{pwm_generator_number}. = PDC_Register;

  //Reactivate the PWM if it was running at the beginning
  if(State)
  { 
    pwm.{pwm_generator_number}._start()
  }
}

void pwm.{pwm_generator_number}._set_frequency(uint32_t frequency)
{
  bool State = PWM_State;
  //Stop the PWM if it is active
  if(State)
  {
    pwm.{pwm_generator_number}._stop()
  }

  Freq = frequency;
  //calculate the value of PTPER according to the pwm frequency
  PTPER_Register = (uint32_t)round((FOSC/(frequency * Prescaler_Register))-1); //Fpwm = Fosc / (Prescaler * (PTPER+1))

  //change PTPER register
  PTPER = PTPER_Register;

  //calculate the duty cycle so that it remains constant even if the frequency changes
  pwm.{pwm_generator_number}._set_duty(Duty_Cycle);

  //Reactivate the PWM if it was running at the beginning
  if(State)
  { 
    pwm.{pwm_generator_number}._start()
  }
}

void pwm.{pwm_generator_number}._set_prescaler(uint8_t prescaler)
{
  bool State = PWM_State;
  //Stop the PWM if it is active
  if(State)
  {
    pwm.{pwm_generator_number}._stop()
  }
  switch(prescaler)
  {
    case 1:
      //change prescaler variable
      Prescaler_Register = 1;
      //change prescaler register
      PTCON2bits.PCLKDIV = 0b000;
      break;
    case 2:
      Prescaler_Register = 2;
      PTCON2bits.PCLKDIV = 0b001;
      break;
    case 4:
      Prescaler_Register = 4;
      PTCON2bits.PCLKDIV = 0b010;
      break;
    case 8:
      Prescaler_Register = 8;
      PTCON2bits.PCLKDIV = 0b011;
      break;
    case 16:
      Prescaler_Register = 16;
      PTCON2bits.PCLKDIV = 0b100;
      break;
    case 32:
      Prescaler_Register = 32;
      PTCON2bits.PCLKDIV = 0b101;
      break;
    case 64:
      Prescaler_Register = 64;
      PTCON2bits.PCLKDIV = 0b110;
      break;
    default:
      break;
  }
  //calculate the frequency so that it remains constant even if the prescaler changes
  pwm.{pwm_generator_number}._set_frequency(Freq);

  //Reactivate the PWM if it was running at the beginning
  if(State)
  { 
    pwm.{pwm_generator_number}._start()
  }
}