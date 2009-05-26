#include "../include/simulator.h"

simtime_t opencell_simtime_get(void)
{
#ifdef SIM_OPNET
    return op_sim_time();
#else
    return (-1);
#endif
}

void * opencell_mem_alloc(size_t size)
{
#ifdef SIM_OPNET
    return op_prg_mem_alloc(size);
#else
    return NULL;
    #endif
}

void opencell_text_output(char* message)
{
    FIN(opencell_text_output());

#ifdef SIM_OPNET
    op_prg_text_output(message);
#endif

    FOUT;
}


