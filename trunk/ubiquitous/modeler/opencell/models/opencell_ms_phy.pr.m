MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A142DDA 4A197040 1A xp Administrator 0 0 none none 0 0 none 456F65D3 CCF 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                               ��g�      @   D   H      �  
�  
�  
�  
�  
�  
�  
�  �           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����             Boolean	\sv_dch_inited;       Evhandle	\rach_try_timer;       Prohandle	\rach_pro;       (Openbts_Frame_Struct*	\frame_struct_ptr;              '#include "../include/openbts_support.h"       /*A request from RR module*/   :#define CALL_REQ (op_intrpt_type()==OPC_INTRPT_REMOTE && \   #	op_intrpt_code()==RR_Phy_Conn_Req)   "#define DCH_INITED (sv_dch_inited)       static void init(void)   {       FIN(init());       A    frame_struct_ptr = (Openbts_Frame_Struct*) openbts_mem_alloc(   $	    sizeof (Openbts_Frame_Struct));       	    FOUT;   }       $static void start_radio_access(void)   {       FIN(start_radio_access());           	    FOUT;   }        static void start_rach(void)   {         FIN(start_radio_access());           7    rach_pro = op_pro_create("opencell_rach", OPC_NIL);   %    op_pro_invoke(rach_pro, OPC_NIL);           	    FOUT;   }                                                      �   �          
   Init   
                                   
   ����   
          pr_state        J   �          
   Idle   
                                       ����             pr_state        �   �          
   	Dedicated   
                                       ����             pr_state        J   Z          
   Wait_Access   
                                       ����             pr_state                        �   �      �   �  A   �          
   tr_0   
       ����          ����              ����             ����                       pr_transition              N  6     =   �   �  5  �  :  V   �          
   tr_2   
       
   default   
       ����              ����             ����                       pr_transition               �   k     9   �   �   �  >   [          
   tr_3   
       
   CALL_REQ   
       
   start_radio_access()   
           ����             ����                       pr_transition              �        b   [     �          
   tr_1   
       
   
DCH_INITED   
       ����              ����             ����                       pr_transition               opencell_rach                                