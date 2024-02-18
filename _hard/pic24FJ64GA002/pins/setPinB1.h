#define TRIS_.{name}.	                _TRISB1
#define PIN_.{name}. 	                _RB1
#define LAT_.{name}. 	                _LATB1
#define ODC_.{name}.	                _ODB1
#define RPOUT_.{name}.		            RPOR0bits.RP1R
#define RPIN_.{name}.		            1
#define CN_.{name}.		                5
#define ADC_value_.{name}.              Buffer_entradas[3] 
#define HAL_SetAnalog_.{name}.()        {_PCFG3=0;\
                                        adc_addAnalogChannel(3);}
