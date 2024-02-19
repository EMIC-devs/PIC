#include <time.h>
#include "inc/timer.h"
#include "inc/system.h"

/*==================[macros]=================================================*/
#define TMR_DISABLED 0x0000
#define TMR_INTERNAL 0x8000
#define TMR_EXTERNAL 0x8002
#define TMR_GATE     0x0040 

#define TMR_DIV_BY_1   0x0000
#define TMR_DIV_BY_8   0x0010
#define TMR_DIV_BY_64  0x0020
#define TMR_DIV_BY_256 0x0030
#define TMR_32_BIT     0x0008 // Only for even numbered timers

#define TMR_HALT_IDLE      0x2000
#define TMR_CONTINUE_IDLE  0x0000

#define T1_EXTERNAL_SYNC  0x8006 //This only applies to Timer1
#define T1_EXTERNAL_RTC   0xC002 //This only applies to Timer1

/*==================[internal data declaration]==============================*/
static Timer4_Callbak_t timer4_Callbak;


//TODO: analizar si es necesario interrupt(auto_psv)

/*==================[funciones privadas]========================================*/

void __attribute__((interrupt(auto_psv))) _T4Interrupt( void )
{
	/* clear interrupt flag */
	IFS1bits.T4IF = 0;

	/* increment ticks counter */
	timer4_Callbak();
}

/*==================[funciones publicas]=========================================*/
void timer4_init (Timer4_Callbak_t callback)
{
	timer4_Callbak = callback;

	#if FOSC==8000000
		T4CON = TMR_INTERNAL | TMR_DIV_BY_8;	        //Interrupcion cada 0.001 Seg a CLK = 8 MH
		PR4 = 500; 										// PR = (tick*FOSC)/(cycles_per_intruction*prescale)
	#endif

	#if FOSC==120000000
		T4CON = TMR_INTERNAL | TMR_DIV_BY_64;			//Interrupcion cada 0.001 Seg a CLK = 120 MH	
		PR4 = 938; 										
	#endif

	#if FOSC==32000000
		T4CON = TMR_INTERNAL | TMR_DIV_BY_64;			//Interrupcion cada 0.001 Seg a CLK = 32 MH
		PR4 = 250; 
	#endif

		/* enable Timer 4 interrupt */
		IEC1bits.T4IE = 1;
}