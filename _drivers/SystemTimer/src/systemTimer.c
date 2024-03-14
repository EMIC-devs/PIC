#include <xc.h>
#include "inc/systemTimer.h"
#include "inc/timer.h"

static uint32_t systemMilis = 0;


uint32_t getSystemMilis()
{
    return systemMilis;
}

void callback()
{
	systemMilis++;
}

void systemTimeInit()
{
    timer4_init (callback);
}
