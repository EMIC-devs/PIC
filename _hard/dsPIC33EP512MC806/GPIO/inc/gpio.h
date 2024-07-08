
#ifndef PIC_GPIO_H_
#define PIC_GPIO_H_

#include "pins.h"

typedef enum
{
	GPIO_OUTPUT,
	GPIO_INPUT,
}gpio_pinConfig_t;

typedef enum
{
	GPIO_LOW,
	GPIO_HIGH,
	GPIO_TOGGLE
}gpio_state_t;



#define HAL_GPIO_PinCfg(name,cfg_value) TRIS_##name = cfg_value
#define HAL_GPIO_PinSet(name,value) PIN_##name = value
#define HAL_GPIO_PinGet(name) PIN_##name


#endif
