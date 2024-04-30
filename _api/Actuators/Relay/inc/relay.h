/*****************************************************************************
  @file     Rele.h

  @brief    API Library to use RELE

  @author   Pentacolo Tomas (based on PL)

  @date     08/06/2023

  @version  1.0.0 - Initial release.
 ******************************************************************************/

#ifndef __RELE_.{name}._H__
#define __RELE_.{name}._H__

EMIC:ifdef(usedFunction.relay_.{name}.)

void initRelay_.{name}.(void);
EMIC:define(inits.initRelay_.{name}.,initRelay_.{name}.)

void relay_.{name}.(uint8_t stateRelay);

EMIC:endif

#endif
