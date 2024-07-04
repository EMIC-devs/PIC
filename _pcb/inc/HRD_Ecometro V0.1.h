EMIC:setOutput(TARGET:inc/systemConfig.h)

// CONFIGURACIONES DEL MICROCONTROLADOR
// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = OFF                // General Segment Code-Protect bit (General Segment Code protect is disabled)
#pragma config GSSK = OFF               // General Segment Key bits (General Segment Write Protection and Code Protection is Disabled)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Initial Oscillator Source Selection bits (Internal Fast RC with PLL (FRCPLL))
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = OFF            // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS16           // Watchdog Timer Postscaler bits (1:16)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Wait Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer always enabled) (pasar a ON para grabar)

// FPOR
#pragma config FPWRT = PWR128           // Power-on Reset Timer Value Select bits (128ms)
#pragma config BOREN = ON               // Brown-out Reset (BOR) Detection Enable bit (BOR is enabled)
#pragma config ALTI2C1 = OFF            // Alternate I2C pins for I2C1 (SDA1/SCK1 pins are selected as the I/O pins for I2C1)

// FICD
#pragma config ICS = PGD3               // ICD Communication Channel Select bits (Communicate on PGEC3 and PGED3)
#pragma config RSTPRI = PF              // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FAS
#pragma config AWRP = OFF               // Auxiliary Segment Write-protect bit (Aux Flash may be written)
#pragma config APL = OFF                // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
#pragma config APLK = OFF   

EMIC:restoreOutput

//--------------------------------------------------------------------------------------------------

EMIC:setOutput(TARGET:inc/system.h)

#define FOSC 46062500  //TODO: se cambio a mano por error de baud en la compu 
#define FCY (FOSC/2)

EMIC:restoreOutput

//--------------------------------------------------------------------------------------------------

EMIC:setOutput(TARGET:inc/pins.h)

#include <xc.h>
#include <libpic30.h>

EMIC:define(system.ucName,dspic33EP512MC806)
EMIC:define(system.i2c,2)

//PROG
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B1,name=PGD)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B0,name=PGC)

//LEDS
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=C12,name=Led1)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B5,name=Led2)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B4,name=Led3)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B3,name=Led4)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B2,name=Led5)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B6,name=Led6)

//MEMORIAS
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=D0,name=MEM_SIO0)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=C13,name=MEM_SIO1)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=C14,name=MEM_SIO2)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=D1,name=MEM_SCK)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=D8,name=MEM_HOLD)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=D9,name=MEM_CS_FLASH)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=D10,name=MEM_CS_RAM1)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=D11,name=MEM_CS_RAM2)

//SWITCHS
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=F0,name=SW1)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=D7,name=SW2)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=D6,name=SW3)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=C15,name=SW4)

//FILTROS
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=F1,name=CLK_PWM_1)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=E0,name=CLK_PWM_2)

//AMP IND
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=,name=PGA_SDO)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=,name=PGA_SDI)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=,name=PGA_SCLK)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=,name=PGA_CS)

//ADC
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B8,name=ADC_RDLa)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B7,name=ADC_RDLb)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=F3,name=ADC_PRE)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B9,name=ADC_Busy)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B10,name=ADC_SDO_B)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B11,name=ADC_SCLK_B)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B12,name=ADC_SCLK_A)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B13,name=ADC_SDO_A)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B14,name=ADC_SDI_A)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=B15,name=ADC_DRL)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=F4,name=ADC_SYNC)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=F5,name=ADC_MCLK)

//POTENCIA
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=E3,name=POT_PWM_INH)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=E2,name=POT_PWM_IN)

//PUERTO
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=F6,name=SDA_)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=G3,name=SDA)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=G2,name=SCL)

//RS232
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=E5,name=RS232_TTL_TX)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=E6,name=RS232_TTL_RX)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=E7,name=RS232_TTL_RTS)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=G6,name=RS232_TTL_CTS)

//AUX
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=G7,name=AUX_RG7)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=G8,name=AUX_RG8)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=G9,name=AUX_RG9)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=E1,name=AUX_RE1)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=E4,name=AUX_RE4)
EMIC:setInput(DEV:_hal/pins/setPin.emic,pin=F2,name=AUX_RF2)

EMIC:restoreOutput
