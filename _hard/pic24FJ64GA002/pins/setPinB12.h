#define TRIS_.{name}.	                _TRISB12
#define PORT_.{name}. 	                _RB12
#define LAT_.{name}. 	                _LATB12
#define ODC_.{name}.	                _ODB12
#define PIN_.{name}. 	                _RB12
#define RPOUT_.{name}.		            RPOR6bits.RP12R
#define RPIN_.{name}.		            12
#define CN_.{name}.		                14
#define ADC_value_.{name}.              Buffer_entradas[12]
#define HAL_SetAnalog_.{name}.()        {_PCFG12=0;\
                                        adc_addAnalogChannel(12);}
