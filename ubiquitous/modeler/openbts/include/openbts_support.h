typedef struct normal_burst
{
    ;
} Openbts_Normal_Burst;

typedef enum
{
    int RACH = 1,
    int DCH
} Openbts_Chan_Type;

typedef struct
{
    int super_frame_seq;
    int multi_frame_seq;
    int TDMA_frame_seq;
    int slot_num;
} Openbts_Frame_Struct;

typedef enum
{
    int Burst_Normal = 1,
    int Burst_Access
} Openbts_Burst_Type;

typedef enum
{
    int User_Conn_Inited = 1, /*PHY->User: the connection is ready. Send your traffic, please.*/
    int Phy_Conn_Req /*User->PHY: I press the "call" button, please make a connection for me.*/
} Openbts_Intrpt_Code;
