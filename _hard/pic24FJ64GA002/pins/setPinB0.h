#define TRIS_.{name}.	                _TRISB0
#define PIN_.{name}. 	                _RB0
#define LAT_.{name}. 	                _LATB0
#define ODC_.{name}.	                _ODB0
#define RPOUT_.{name}.		            RPOR0bits.RP0R
#define RPIN_.{name}.		            0
#define CN_.{name}.		                4
#define ADC_value_.{name}.              Buffer_entradas[2]
#define HAL_SetAnalog_.{name}.()        {_PCFG2=0;\
                                        adc_addAnalogChannel(2);}