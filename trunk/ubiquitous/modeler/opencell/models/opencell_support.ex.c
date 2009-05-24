include "../include/openbts_support.h"

Openbts_Func_Fin_Status 
cur_frame_calc (Openbts_Frame_Struct* frame_struct, simtime_t cur_time);

{
    int cur_slot_num;

    FIN(cur_frame_calc(frame_struct, cur_time));

    assert(frame_struct);

    cur_slot_num = (int)(cur_time-global_share->start_of_epoch)/SLOT_DURATION;
    frame_struct->ts_seq = cur_slot_num % SLOT_PER_FRAME;
    frame_struct->hyper_frame_seq = (int) frame_struct->slot_num / SLOT_PER_HYPERFRAME;
    frame_struct->super_frame_seq = frame_struct->slot_num / SLOT_PER_SUPERFRAME;
    if (frame_struct->super_frame_seq>=2048) frame_struct->super_frame_seq %= 2048;
    
    /*how many TDMA frames are there?*/
    frame_struct->TDMA_frame_seq = (int) (frame_struct->slot_num / SLOT_PER_FRAME);
    if (frame_struct->multiframe_type==Openbts_Ctrl) {
	frame_struct->multi_frame_seq = (int) (frame_struct->tdma_frame_seq / 51);
	frame_struct->tdma_frame_seq %= 51;
    } else {
	frame_struct->multi_frame_seq = (int) (frame_struct->tdma_frame_seq / 26);
	frame_struct->tdma_frame_seq %= 26;
    }

    FRET (OPENBTS_SUCCESS);
}

void frame_struct_debug (Openbts_Frame_Struct* frame_struct)
{
    char message[1024];

    FIN(frame_struct_debug(frame_struct));

    //openbts_print ();
    sprintf(message, "hyperframe: %d\nsuperframe: %d\nhyperframe: %d\nTDMA frame: %d\nTS%d\n\n",
	    frame_struct->hyper_frame_seq,
	    frame_struct->super_frame_seq,
	    frame_struct->multi_frame_seq,
	    frame_struct->tdma_frame_seq,
	    frame_struct->ts_seq);

    op_prg_text_output(message);

    FOUT;
}



