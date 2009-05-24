include "../include/openbts_support.h"

Openbts_Frame_Struct* cur_frame_calc(void)
{
    simtime_t cur_time;
    int cur_slot_num;
    Openbts_Frame_Struct * frame_struct;

    FIN(cur_frame_calc());

    frame_struct = (Openbts_Frame_Struct*) openbts_mem_alloc (sizeof (Openbts_Frame_Struct));

    cur_time = sim_time_get();
    cur_slot_num = (int)(cur_time-global_share->start_of_epoch)/SLOT_DURATION;
    frame_struct->slot_num = cur_slot_num % SLOT_PER_FRAME;

    FOUT;
}
