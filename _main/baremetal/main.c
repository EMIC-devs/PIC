#include <xc.h>

#include "userFncFile.h"  //No RFI scan
#include "userVars.h"  //No RFI scan

#include "userFncFile.c"  //No RFI scan

// #newRFIcode(_hal/system/init.emic) 

// char presist_ persistEnd;
// char presistArray_ persistArrayEnd[2];

int main(void)
{
	//initSystem();
	EMIC:ifdef usedEvent.SystemConfig
	SystemConfig();
	EMIC:endif
	.{inits.*}.();
	EMIC:ifdef usedEvent.onReset
	onReset();
	EMIC:endif
	do
	{
		.{polls.*}.();
	}
	while(1);
}
