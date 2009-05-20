typedef struct normal_burst
{
    ;
} Openbts_Normal_Burst;

typedef enum
{
    int RACH = 1,
    int DCH
} Chan_Type;

typedef struct
{
    int super_frame_seq;
    int multi_frame_seq;
    int TDMA_frame_seq;
    int slot_num;
} Frame_Struct;
