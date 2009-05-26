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

typedef enum
{
    Opencell_TCH_HS = 1,
    Opencell_TCH_FS
} Opencell_Traf_Chan_Type;

typedef enum
{
    Opencell_BCCH = 3,
    Opencell_FCCH,
    Opencell_SCH
  
} Opencell_Broadcast_Chan_Type;

typedef enum
{
Opencell_PCH = 6,
Opencell_RACH,
Opencell_AGCH

} Opencell_Common_Ctrl_Chan_Type;

typedef enum
{
Opencell_SDCCH = 9,
Opencell_SACCH,
Opencell_FACCH
} Opencell_Dedicated_Ctrl_Chan_Type;

typedef enum
{
    Burst_Normal = 1,
    Burst_Access
} Opencell_Burst_Type;

typedef enum
{
    Opencell_Burst_Fd_Index_Type=0, /*For simulation purpose only, not an actual burst field*/
    Opencell_Burst_Fd_Index_Payload=1,
    Opencell_Burst_Fd_Index_Overhead /*Overhead includes Training Sequence and Tail Bit*/
} Opencell_Burst_Fd_Index;

typedef enum Opencell_Burst_Payload_Size
{
    Opencell_Burst_Payload_Size_NB = (57*2),  /*Normal Burst*/
    Opencell_Burst_Payload_Size_FCB = 142,  /*Frequency Correction Burst*/
    Opencell_Burst_Payload_Size_AB = 36
} Opencell_Burst_Payload_Size;

typedef enum Opencell_Burst_Overhead_Size
{
    Opencell_Burst_Overhead_Size_NB = (3*2 + 26),
    Opencell_Burst_Overhead_Size_FCB = (3*2),
    Opencell_Burst_Overhead_Size_AB = (3*2+41)
} Opencell_Burst_Overhead_Size;

/*
typedef struct
{
;
} Opencell_Normal_Burst;
*/

typedef enum
{
    Phy_User_Conn_Inited = 1, /*PHY->User: the connection is ready. Send your traffic, please.*/
    Phy_RR_Conn_Inited,  /*PHY->RR: the connection is ready. Send your signalling, please.*/
    User_RR_Conn_Req, /*User->RR: I press the "call" button, please make a connection for me.*/
    RR_Phy_Conn_Req /*RR->Phy: I have signalling to do, please make a connection for me.*/
} Opencell_Intrpt_Code;


typedef struct
{
    Objid	rr_objid;
    Objid	user_objid;
    int	rr_ostrm;
    int	user_ostrm;
    int tx_ostrm;
    int tx_istrm;
    int rr_istrm;
    int user_istrm;
    List* rr_sig_lptr; /*List containing signalling packets from RR*/
} Opencell_Phy_Mod_Data;


/*Function prototypes*/
Opencell_Func_Fin_Status 
opencell_cur_frame_calc (Opencell_Frame_Struct* frame_struct, simtime_t cur_time);

void opencell_frame_struct_debug (Opencell_Frame_Struct* frame_struct);


extern Opencell_Global_Share * global_share;

#endif

