#include "../include/opencell_support.h"

simtime_t opencell_next_slot (simtime_t cur_time)
{
    simtime_t next_slot_time;
    simtime_t delta;

    FIN(opencell_next_slot() );

    delta = cur_time % SLOT_DURATION;
    next_slot_time = cur_time - delta;


    FRET (next_slot_time);
}

Opencell_Func_Fin_Status 
opencell_cur_frame_calc (Opencell_Frame_Struct* frame_struct, simtime_t cur_time)
{
    int cur_slot_num;

    FIN(opencell_cur_frame_calc(frame_struct, cur_time));

    assert(frame_struct);

    cur_slot_num = (int)(cur_time-global_share->start_of_epoch)/SLOT_DURATION;
    frame_struct->ts_seq = cur_slot_num % SLOT_PER_FRAME;
    frame_struct->hyper_frame_seq = (int) frame_struct->slot_num / SLOT_PER_HYPERFRAME;
    frame_struct->super_frame_seq = frame_struct->slot_num / SLOT_PER_SUPERFRAME;
    if (frame_struct->super_frame_seq>=2048) frame_struct->super_frame_seq %= 2048;
    
    /*how many TDMA frames are there?*/
    frame_struct->TDMA_frame_seq = (int) (frame_struct->slot_num / SLOT_PER_FRAME);
    if (frame_struct->multiframe_type==Opencell_Ctrl) {
	frame_struct->multi_frame_seq = (int) (frame_struct->tdma_frame_seq / 51);
	frame_struct->tdma_frame_seq %= 51;
    } else {
	frame_struct->multi_frame_seq = (int) (frame_struct->tdma_frame_seq / 26);
	frame_struct->tdma_frame_seq %= 26;
    }

    FRET (OPENCELL_SUCCESS);
}

void opencell_frame_struct_debug (Opencell_Frame_Struct* frame_struct)
{
    char message[1024];

    FIN(opencell_frame_struct_debug(frame_struct));

    //opencell_print ();
    sprintf(message, "hyperframe: %d\nsuperframe: %d\nhyperframe: %d\nTDMA frame: %d\nTS%d\n\n",
	    frame_struct->hyper_frame_seq,
	    frame_struct->super_frame_seq,
	    frame_struct->multi_frame_seq,
	    frame_struct->tdma_frame_seq,
	    frame_struct->ts_seq);

    opencell_text_output(message);

    FOUT;
}



