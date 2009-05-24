#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#define SIM_OPNET 0
#define SIM_OMNET 1

#define double simtime_t

simtime_t openbts_simtime_get(void);
void openbts_print(char* string);

#endif
