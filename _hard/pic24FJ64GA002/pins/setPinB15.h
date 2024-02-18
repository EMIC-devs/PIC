#define TRIS_.{name}.	                _TRISB15
#define PORT_.{name}. 	                _RB15
#define LAT_.{name}. 	                _LATB15
#define ODC_.{name}.	                _ODB15
#define PIN_.{name}. 	                _RB15
#define RPOUT_.{name}.	                RPOR7bits.RP15R
#define RPIN_.{name}.	                15
#define CN_.{name}.		                11
#define ADC_value_.{name}.              Buffer_entradas[9] 
#define HAL_SetAnalog_.{name}.()        {_PCFG9=0;\
                                        adc_addAnalogChannel(9);}