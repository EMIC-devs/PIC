#define TRIS_.{name}.	                _TRISA0
#define PORT_.{name}. 	                _A0
#define LAT_.{name}. 	                _LATA0
#define ODC_.{name}.	                _ODA0
#define PIN_.{name}. 	                _RA0
#define CN_.{name}.		                2
#define ADC_value_.{name}.              Buffer_entradas[0] 
#define HAL_SetAnalog_.{name}.()        {_PCFG0=0;\
                                        adc_addAnalogChannel(0);}

