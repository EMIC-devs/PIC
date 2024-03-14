
#ifndef _TIMER_.{name}._API_H_
#define _TIMER_.{name}._API_H_

#include <xc.h>

EMIC:ifdef usedFunction.setTime.{name}.
void setTime.{name}.(uint32_t setPoint, char l_modo);
EMIC:endif

EMIC:ifdef usedEvent.etOut.{name}.
void timer.{name}._Poll(void);
EMIC:define(polls.timer.{name}._Poll,timer.{name}._Poll)
EMIC:endif

/*==================[end of file]============================================*/
#endif
