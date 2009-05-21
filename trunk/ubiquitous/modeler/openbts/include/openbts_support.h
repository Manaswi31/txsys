#define SLOT_DURATION 4.7815
#define VOICE_INTVL SLOT_DURATION

typedef struct normal_burst
{
} Openbts_Normal_Burst;

typedef struct
{
    int super_frame_seq;
    int multi_frame_seq;
    int TDMA_frame_seq;
    int slot_num;
} Openbts_Frame_Struct;

typedef enum _Openbts_Chan_Type
{
    RACH = 1,
    DCH,
    AGCH,
    PCH,
    TCH_HS,
    TCH_FS
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
