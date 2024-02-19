#include <xc.h>

void LEDs_.{name}._init (void);
EMIC:define(inits.LEDs_,LEDs_.{name}._init)

EMIC:ifdef usedFunction.LEDs_.{name}._blink
void LEDs_.{name}._poll (void);
EMIC:define(polls.LEDs_.{name}.,LEDs_.{name}._poll)
EMIC:endif

EMIC:ifdef usedFunction.LEDs_.{name}._state
void LEDs_.{name}._state(uint8_t);
EMIC:endif

EMIC:ifdef usedFunction.LEDs_.{name}._blink
void LEDs_.{name}._blink(uint16_t, uint16_t, uint16_t);
EMIC:endif
