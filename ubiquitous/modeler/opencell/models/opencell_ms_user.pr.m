MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A13C8C9 4A1ABF28 27 lenovo-636778b4 Administrator 0 0 none none 0 0 none 2A75A301 1030 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                 ��g�      @   �   �  �  �  �          $  (  ,  �      User TrafficOn_Off   �������   ����           ����          ����          ����           �Z                 	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����             Boolean	\sv_traf_on_flag;       Objid	\sv_phy_objid;       int	\sv_out_strm;       Objid	\sv_rr_objid;          int intrpt_code;   int intrpt_type;      (#include "../include/opencell_support.h"   /#define NO_TRAFFIC (sv_traf_on_flag==OPC_FALSE)   8#define CALL_SUCCESS (intrpt_code==Phy_User_Conn_Inited)   1#define GEN_INTRPT (intrpt_type==OPC_INTRPT_SELF)   "   #static void press_call_button(void)   {       FIN(press_call_button());       ,    /*Tell RR that I'd like to make a call*/   M    op_intrpt_schedule_remote (op_sim_time(), User_RR_Conn_Req, sv_rr_objid);       	    FOUT;   }       static void gen(void)   	{   	Packet * pkptr;       	FIN(gen());       =	/*partitioning and interleaving are currently not modeled.*/   *	/*payload of a normal burst is 114 bits*/   	pkptr = op_pk_create(0);       ?	/*For a normal burst, the contents of fields are not modeled*/   M	op_pk_fd_set(pkptr, Opencell_Burst_Fd_Index_Type, OPC_FIELD_TYPE_UNSPEC, 0);   R	op_pk_fd_set(pkptr, Opencell_Burst_Fd_Index_Overhead, OPC_FIELD_TYPE_UNSPEC, 34);   R	op_pk_fd_set(pkptr, Opencell_Burst_Fd_Index_Payload, OPC_FIELD_TYPE_UNSPEC, 114);   	   	        	op_pk_send(pkptr, sv_out_strm);   	   	   9	op_intrpt_schedule_self(op_sim_time() + VOICE_INTVL, 0);   	   	FOUT;   	}                                          Z   Z          
   Init   
       
      Objid node_objid;   *node_objid = op_topo_parent(op_id_self());   Esv_phy_objid = op_id_from_name (node_objid, OPC_OBJTYPE_PROC, "phy");   Csv_rr_objid = op_id_from_name (node_objid, OPC_OBJTYPE_PROC, "RR");   Fop_ima_obj_attr_get_toggle(op_id_self(), "On_Off", & sv_traf_on_flag);   sv_out_strm = 0;       
                     
   ����   
          pr_state        �   �          
   Wait   
                                       ����             pr_state          J          
   No_traf   
                                       ����             pr_state        �   Z          
   Wait_Call_Setup   
       
      press_call_button();   
       
      intrpt_code = op_intrpt_code();   
           ����             pr_state                         �     �   �  �  H  �   �  �   �          
   tr_0   
       
   
GEN_INTRPT   
       
   gen()   
       
    ����   
          ����                       pr_transition                �   �      T   h    D          
   tr_2   
       
   
NO_TRAFFIC   
       ����          
    ����   
          ����                       pr_transition                �   L      f   V  y   d          
   tr_1   
       
   ! NO_TRAFFIC   
       ����          
    ����   
          ����                       pr_transition              �   �     �   f  �   �          
   tr_4   
       
   CALL_SUCCESS   
       ����          
    ����   
          ����                       pr_transition                                             