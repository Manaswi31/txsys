/**
 * @author
 * illidan.modeler@gmail.com
 */

#ifndef __OPENBTS_SUPPORT_H__
#define __OPENBTS_SUPPORT_H__

#include "simulator.h"
#include <assert.h>

#define SLOT_DURATION 4.7815
#define SLOT_PER_FRAME 8
#define SLOT_PER_TRAF_MULTIFRAME (26*SLOT_PER_FRAME)
#define SLOT_PER_CTRL_MULTIFRAME (51*SLOT_PER_FRAME)
#define SLOT_PER_SUPERFRAME (SLOT_PER_TRAF_MULTIFRAME * 51)
#define SLOT_PER_HYPERFRAME (2048*SLOT_PER_SUPERFRAME)
#define VOICE_INTVL SLOT_DURATION

typedef struct
{
    simtime_t start_of_epoch; /*Start of time slots*/
} Openbts_Global_Share;

typedef struct normal_burst
{
} Openbts_Normal_Burst;

typedef enum 
{
    Openbts_Ctrl = 1,
    Openbts_Traf
} Openbts_Multiframe_Type;

typedef struct
{
    int hyper_frame_seq;
    int super_frame_seq;
    Openbts_Multiframe_Type multiframe_type;
    int multi_frame_seq;
    int tdma_frame_seq;
    int ts_seq;
} Openbts_Frame_Struct;

typedef enum
{
    OPENBTS_SUCCESS = 1,
    OPNEBTS_FAILURE = -1
} Openbts_Func_Fin_Status;

typedef enum _Openbts_Chan_Type
{
    Openbts_RACH = 1,
    Openbts_DCH,
    Openbts_AGCH,
    Openbts_PCH,
    Openbts_TCH_HS,
    Openbts_TCH_FS
} Openbts_Chan_Type;

typedef enum
{
    Burst_Normal = 1,
    Burst_Access
} Openbts_Burst_Type;

typedef enum
{
    Openbts_Burst_Fd_Index_Category=0, /*For simulation purpose only, not an actual burst field*/
    Openbts_Burst_Fd_Index_Payload=1,
    Openbts_Burst_Fd_Index_Overhead,
} Openbts_Burst_Fd_Index;

typedef enum
{
    User_Conn_Inited = 1, /*PHY->User: the connection is ready. Send your traffic, please.*/
    Phy_Conn_Req /*User->PHY: I press the "call" button, please make a connection for me.*/
} Openbts_Intrpt_Code;

extern Openbts_Global_Share * global_share;


/*Function prototypes*/
Openbts_Func_Fin_Status 
cur_frame_calc (Openbts_Frame_Struct* frame_struct, simtime_t cur_time);

void frame_struct_debug (Openbts_Frame_Struct* frame_struct);


#endif
