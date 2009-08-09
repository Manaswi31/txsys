#include "ra.h"

double tr_len_ack;
double tr_len_retx;
int max_retx_times;

void g_init(void)
{

    FIN(g_init);

    //TODO: read in the attribute from the model
    tr_len_ack = 5.0;
    tr_len_retx = op_dist_exponential(1.0);
    max_retx_times = 3;

    FOUT;
}


