/**
 * @author
 * illidan.modeler@gmail.com
 */

#ifndef __OPENCELL_SUPPORT_H__
#define __OPENCELL_SUPPORT_H__

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
} Opencell_Global_Share;

typedef struct normal_burst
{
} Opencell_Normal_Burst;

typedef enum 
{
    Opencell_Ctrl = 1,
    Opencell_Traf
} Opencell_Multiframe_Type;

typedef struct
{
    int hyper_frame_seq;
    int super_frame_seq;
    Opencell_Multiframe_Type multiframe_type;
    int multi_frame_seq;
    int tdma_frame_seq;
    int ts_seq;
} Opencell_Frame_Struct;

typedef enum
{
    OPENCELL_SUCCESS = 1,
    OPNEBTS_FAILURE = -1
} Opencell_Func_Fin_Status;

typedef enum _Opencell_Chan_Type
{
    Opencell_RACH = 1,
    Opencell_DCH,
    Opencell_AGCH,
    Opencell_PCH,
    Opencell_TCH_HS,
    Opencell_TCH_FS
} Opencell_Chan_Type;

typedef enum
{
    Burst_Normal = 1,
    Burst_Access
} Opencell_Burst_Type;

typedef enum
{
    Opencell_Burst_Fd_Index_Category=0, /*For simulation purpose only, not an actual burst field*/
    Opencell_Burst_Fd_Index_Payload=1,
    Opencell_Burst_Fd_Index_Overhead,
} Opencell_Burst_Fd_Index;

typedef enum
{
    User_Conn_Inited = 1, /*PHY->User: the connection is ready. Send your traffic, please.*/
    Phy_Conn_Req /*User->PHY: I press the "call" button, please make a connection for me.*/
} Opencell_Intrpt_Code;

extern Opencell_Global_Share * global_share;


/*Function prototypes*/
Opencell_Func_Fin_Status 
cur_frame_calc (Opencell_Frame_Struct* frame_struct, simtime_t cur_time);

void frame_struct_debug (Opencell_Frame_Struct* frame_struct);


#endif
