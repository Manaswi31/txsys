MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A142DDA 4A1A1541 28 lenovo-636778b4 Administrator 0 0 none none 0 0 none DA73B8BE 10C5 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                 ��g�      @   D   H      	�  �  �  �  �  �  �  �  	�           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����          
   Boolean	\sv_dch_inited;       Evhandle	\rach_try_timer;       Prohandle	\rach_pro;       (Openbts_Frame_Struct*	\frame_struct_ptr;       )Opencell_Phy_Mod_Data*	\phy_mod_data_ptr;              '#include "../include/openbts_support.h"       /*A request from RR module*/   :#define CALL_REQ (op_intrpt_type()==OPC_INTRPT_REMOTE && \   #	op_intrpt_code()==RR_Phy_Conn_Req)   "#define DCH_INITED (sv_dch_inited)       ;   static void init(void)   {   	Objid node_objid;   	       FIN(init());       A    frame_struct_ptr = (Openbts_Frame_Struct*) openbts_mem_alloc(   $	    sizeof (Openbts_Frame_Struct));   +	node_objid = op_topo_parent(op_id_self());       	/*   !	stream    :  phy [0] -> rt_0 [0]   stream    :  phy [1] -> RR [0]    stream    :  rr_0 [0] -> phy [0]    stream    :  user [0] -> phy [1]   stream    :  RR [0] -> phy [2]   	*/       `phy_mod_data_ptr = (Opencell_Phy_Mod_Data*) opencell_mem_alloc (sizeof (Opencell_Phy_Mod_Data));   S	phy_mod_data_ptr->rr_objid = op_id_from_name (node_objid, OPC_OBJTYPE_PROC, "RR");   W	phy_mod_data_ptr->user_objid = op_id_from_name (node_objid, OPC_OBJTYPE_PROC, "user");   !		phy_mod_data_ptr->rr_ostrm = 1;   "	phy_mod_data_ptr->user_ostrm = 2;    	phy_mod_data_ptr->tx_ostrm = 0;   )	op_pro_modmem_install(phy_mod_data_ptr);   	   	   	    FOUT;   }       $static void start_radio_access(void)   {   	simtime_t next_slot_time;   	simtime_t cur_time;   	       FIN(start_radio_access());   	   #	cur_time = opencell_simtime_get();   /	next_slot_time = opencell_next_slot(cur_time);   B	op_intrpt_schedule_call (next_slot_time, 0, start_rach, OPC_NIL);           	    FOUT;   }        1static void start_rach(void* state_ptr, int code)   {         FIN(start_rach());           7    rach_pro = op_pro_create("opencell_rach", OPC_NIL);   %    op_pro_invoke(rach_pro, OPC_NIL);           	    FOUT;   }                                                      �   �          
   Init   
       
      init();   
                     
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