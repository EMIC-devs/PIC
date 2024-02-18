#define TRIS_.{name}.	_TRISA1
#define LAT_.{name}. 	_LATA1
#define ODC_.{name}.	_ODA1
#define PIN_.{name}. 	_RA1
#define CN_.{name}.		3
#define ADC_value_.{name}.              Buffer_entradas[1] 
#define HAL_SetAnalog_.{name}.()        {_PCFG1=0;\
                                        adc_addAnalogChannel(1);}
