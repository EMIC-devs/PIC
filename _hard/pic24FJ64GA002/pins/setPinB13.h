#define TRIS_.{name}.	                _TRISB13
#define PORT_.{name}. 	                _RB13
#define LAT_.{name}. 	                _LATB13
#define ODC_.{name}.	                _ODB13
#define PIN_.{name}. 	                _RB13
#define RPOUT_.{name}.		            RPOR6bits.RP13R
#define RPIN_.{name}.		            13
#define CN_.{name}.		                13
#define ADC_value_.{name}.              Buffer_entradas[11] 
#define HAL_SetAnalog_.{name}.()        {_PCFG11=0;\
                                        adc_addAnalogChannel(11);}
