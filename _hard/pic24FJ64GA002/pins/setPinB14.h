#define TRIS_.{name}.	                _TRISB14
#define PORT_.{name}. 	                _RB14
#define LAT_.{name}. 	                _LATB14
#define ODC_.{name}.	                _ODB14
#define PIN_.{name}. 	                _RB14
#define RPOUT_.{name}.	                RPOR7bits.RP14R
#define RPIN_.{name}.	                14
#define CN_.{name}.		                12
#define ADC_value_.{name}.              Buffer_entradas[10] 
#define HAL_SetAnalog_.{name}.()        {_PCFG10=0;\
                                        adc_addAnalogChannel(10);}
