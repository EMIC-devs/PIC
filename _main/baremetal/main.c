#include <xc.h>
#include "inc/systemConfig.h"

#include "inc/.{main_includes.*}..h"
#include "inc/.{includes_head.*}..h"

#include "inc/userFncFile.h"
#include "inc/userVars.h"


#include ".{includes_src.*}..c"

// char presist_ persistEnd;
// char presistArray_ persistArrayEnd[2];

int main(void)
{
	initSystem();
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
