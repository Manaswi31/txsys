MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A142DDA 4A1E96D4 37 lenovo-636778b4 Administrator 0 0 none none 0 0 none C2E1B58F 1507 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                 ��g�      @   D   H        �  �  �  �  �  �    �           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����          
   Boolean	\sv_dch_inited;       Evhandle	\rach_try_timer;       Prohandle	\rach_pro;       )Opencell_Frame_Struct*	\frame_struct_ptr;       )Opencell_Phy_Mod_Data*	\phy_mod_data_ptr;              (#include "../include/opencell_support.h"       /*A request from RR module*/   q#define CALL_REQ ((op_intrpt_type()==OPC_INTRPT_REMOTE) && (op_intrpt_source ()==phy_mod_data_ptr->rr_objid) && \   %	(op_intrpt_code()==RR_Phy_Conn_Req))       <#define RR_SIG_ARRVL (op_intrpt_type()==OPC_INTRPT_STRM && \   .	op_intrpt_strm()==phy_mod_data_ptr->rr_istrm)       "#define DCH_INITED (sv_dch_inited)       static void init(void);   2static void start_rach(void* state_ptr, int code);   %static void start_radio_access(void);    static void rr_sig_handle(void);   Q   static void init(void)   {   	Objid node_objid;   	       FIN(init());       C    frame_struct_ptr = (Opencell_Frame_Struct*) opencell_mem_alloc(   %	    sizeof (Opencell_Frame_Struct));   +	node_objid = op_topo_parent(op_id_self());       	/*   stream    :  phy [0] -> tx [0]   stream    :  phy [1] -> RR [0]    stream    :  phy [2] -> user [0]   stream    :  rx [0] -> phy [0]    stream    :  user [0] -> phy [1]   stream    :  RR [0] -> phy [2]   	*/       a	phy_mod_data_ptr = (Opencell_Phy_Mod_Data*) opencell_mem_alloc (sizeof (Opencell_Phy_Mod_Data));   S	phy_mod_data_ptr->rr_objid = op_id_from_name (node_objid, OPC_OBJTYPE_PROC, "RR");   W	phy_mod_data_ptr->user_objid = op_id_from_name (node_objid, OPC_OBJTYPE_PROC, "user");   	    	phy_mod_data_ptr->rr_ostrm = 1;   "	phy_mod_data_ptr->user_ostrm = 2;    	phy_mod_data_ptr->tx_ostrm = 0;   	    	phy_mod_data_ptr->rr_istrm = 2;   "	phy_mod_data_ptr->user_istrm = 1;    	phy_mod_data_ptr->rx_istrm = 0;   	   6	phy_mod_data_ptr->rr_sig_lptr = op_prg_list_create();   )	op_pro_modmem_install(phy_mod_data_ptr);   	   	   	    FOUT;   }       $static void start_radio_access(void)   {   	simtime_t next_slot_time;   	simtime_t cur_time;   	       FIN(start_radio_access());   	   #	cur_time = opencell_simtime_get();   /	next_slot_time = opencell_next_slot(cur_time);   B	op_intrpt_schedule_call (next_slot_time, 0, start_rach, OPC_NIL);           	    FOUT;   }        1static void start_rach(void* state_ptr, int code)   {         FIN(start_rach());           7    rach_pro = op_pro_create("opencell_rach", OPC_NIL);   %    op_pro_invoke(rach_pro, OPC_NIL);           	    FOUT;   }       static void rr_sig_handle(void)   	{   	Packet *rr_sig_pkptr;   	   	FIN(rr_sig_handle());   	   6	rr_sig_pkptr = op_pk_get(phy_mod_data_ptr->rr_istrm);   W	/*op_prg_list_insert(phy_mod_data_ptr->rr_sig_lptr, rr_sig_pkptr, OPC_LISTPOS_TAIL);*/   	op_pk_destroy(rr_sig_pkptr);   	   	FOUT;   	}                                                          �  J          
   Init   
       
      init();   
                     
   ����   
          pr_state        J  J          
   Idle   
                                       ����             pr_state        �  J          
   	Dedicated   
                                       ����             pr_state        J   �          
   Wait_Access   
                                       ����             pr_state                        �  G      �  D  A  J          
   tr_0   
       ����          ����              ����             ����                       pr_transition              N  �     =  \   �  �  �  �  V  X          
   tr_2   
       
   default   
       ����              ����             ����                       pr_transition               �   �     9  =   �     >   �          
   tr_3   
       
   CALL_REQ   
       
   start_radio_access()   
           ����             ����                       pr_transition              �   �     b   �    L          
   tr_1   
       
   
DCH_INITED   
       ����              ����             ����                       pr_transition              @   �     2   �     �  �   �  Z   �          
   tr_4   
       
   RR_SIG_ARRVL   
       
   rr_sig_handle()   
       
    ����   
          ����                       pr_transition               opencell_rach                                