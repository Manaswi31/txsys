MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A13C8C9 4A1519C8 1D op-demo-1 wjb 0 0 none none 0 0 none 83317381 DAD 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                                  ��g�      @   �   �  �  �  �  �  �  �  �  �  �  �  w      User TrafficOn_Off   �������   ����           ����          ����          ����           �Z                 	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����             Boolean	\sv_traf_on_flag;       Objid	\sv_phy_objid;       int	\sv_out_strm;          int intrpt_code;      '#include "../include/openbts_support.h"   /#define NO_TRAFFIC (sv_traf_on_flag==OPC_FALSE)   4#define CALL_SUCCESS (intrpt_code==User_Conn_Inited)      #static void press_call_button(void)   {       FIN(press_call_button());       -    /*Tell PHY that I'd like to make a call*/   J    op_intrpt_schedule_remote (op_sim_time(), Phy_Conn_Req, sv_phy_objid);       	    FOUT;   }       static void gen(void)   	{   	Packet * pkptr;   	FIN(gen());   	pkptr = op_pk_create(114);    	op_pk_send(pkptr, sv_out_strm);   	   	   9	op_intrpt_schedule_self(op_sim_time() + VOICE_INTVL, 0);   	   	FOUT;   	}                                          Z   Z          
   Init   
       J      Objid node_objid;   *node_objid = op_topo_parent(op_id_self());   Esv_phy_objid = op_id_from_name (node_objid, OPC_OBJTYPE_PROC, "phy");   Fop_ima_obj_attr_get_toggle(op_id_self(), "On_Off", & sv_traf_on_flag);   sv_out_strm = 0;       J                     
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
           ����             pr_state                         �     �   �  �  H  �   �  �   �          
   tr_0   
       ����          
   gen()   
       
    ����   
          ����                       pr_transition                �   �      T   h    D          
   tr_2   
       J   
NO_TRAFFIC   J       ����          
    ����   
          ����                       pr_transition                �   L      f   V  y   d          
   tr_1   
       J   ! NO_TRAFFIC   J       ����          
    ����   
          ����                       pr_transition              �   �     �   f  �   �          
   tr_4   
       
   CALL_SUCCESS   
       ����          
    ����   
          ����                       pr_transition                                             