#define TRIS_.{name}.	                _TRISB2
#define PIN_.{name}. 	                _RB2
#define LAT_.{name}. 	                _LATB2
#define ODC_.{name}.	                _ODB2
#define RPOUT_.{name}.		            RPOR1bits.RP2R
#define RPIN_.{name}.		            2
#define CN_.{name}.		                6
#define ADC_value_.{name}.              Buffer_entradas[4] 
#define HAL_SetAnalog_.{name}.()        {_PCFG4=0;\
                                        adc_addAnalogChannel(4);}
