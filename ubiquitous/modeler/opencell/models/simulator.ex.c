#include "../include/simulator.h"

simtime_t opencell_simtime_get(void)
{
#ifdef SIM_OPNET
    return op_sim_time();
#else
    return (-1);
}

void * opencell_mem_alloc(size_t size)
{
#ifdef SIM_OPNET
    return op_prg_mem_alloc(size);
#else
    return NULL;
}
