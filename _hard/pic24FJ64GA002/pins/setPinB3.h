#define TRIS_.{name}.	                _TRISB3
#define LAT_.{name}. 	                _LATB3
#define ODC_.{name}.	                _ODB3
#define PIN_.{name}. 	                _RB3
#define RPOUT_.{name}.	                RPOR1bits.RP3R
#define RPIN_.{name}.	                3
#define CN_.{name}.		                7
#define ADC_value_.{name}.              Buffer_entradas[5] 
#define HAL_SetAnalog_.{name}.()        {_PCFG5=0;\
                                        adc_addAnalogChannel(5);}
