/*****************************************************************************
  @file     EMICBus.h

  @brief    API Library to use emic bus

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @date 	04/03/2024

  @version  v0.0.1
 ******************************************************************************/

void emicBus_init(void);
EMIC:define(inits.emicBus_init,emicBus_init)

void pI2C(char* format,...);

void poll_emicBus(void);
EMIC:define(polls.poll_emicBus,poll_emicBus)