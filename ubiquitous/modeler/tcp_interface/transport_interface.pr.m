MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A71CCE0 4A786135 19 q300t wjb 0 0 none none 0 0 none 1977BB01 10F7 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                     ��g�      @   �   �  �  �  �  �  �  �  �  �  �  �  �      Client or Server   �������   ����             Client          ����          ����         Client      ����      Server       ����       �Z                 	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����             Boolean	\pasv_active;        ApiT_Tcp_App_Handle	\tcp_handle;       Objid	\my_objid;          +TcpT_Conn_Open_Options		local_conn_options;   int tcp_connection_id;   int rem_port;   IpT_Address my_ipaddr;   IpT_Address rem_addr;       Packet * pkptr;      *#include <ip_higher_layer_proto_reg_sup.h>   #include "ip_rte_support.h"           Q#define TIMER_OPEN_ACTIVE (op_intrpt_type()== OPC_INTRPT_SELF && (!pasv_active) )   2#define PKT_IN (op_intrpt_type()==OPC_INTRPT_STRM)                                                J   �          
   Init   
       J          	       my_objid = op_id_self();       Lop_ima_obj_attr_get_toggle(op_id_self(), "Client or Server", & pasv_active);       if (pasv_active)   	{   9	tcp_conn_open_default_options_set (&local_conn_options);   B	tcp_conn_open_options_local_port_set (&local_conn_options, 5800);   Y	tcp_connection_id = tcp_connection_open_with_options(&tcp_handle,INETC_ADDRESS_INVALID,    E		TCPC_PORT_UNSPEC, TCPC_COMMAND_OPEN_PASSIVE, & local_conn_options);   	}       .op_intrpt_schedule_self(op_sim_time()+0.1, 0);   J                     J   ����   J          pr_state        �   �          
   Wait   
                                       ����             pr_state        v   �          J   	Proc_Data   J       J      #//tcp_send_data(tcp_handle, pkptr);       J                     
   ����   
          pr_state        �  J          J   Open_Active   J       J          	{   )	tcp_handle = tcp_app_register(my_objid);   9	tcp_conn_open_default_options_set (&local_conn_options);   B	tcp_conn_open_options_local_port_set (&local_conn_options, 5800);   K	my_ipaddr = ip_support_address_from_node_id_get(op_topo_parent(my_objid));   m	tcp_conn_open_options_local_addr_set(&local_conn_options,inet_address_from_ipv4_address_create (my_ipaddr));   -	rem_addr = ip_address_create("192.168.1.1");   	rem_port = 5800;   a	tcp_connection_open_with_options(& tcp_handle, inet_address_from_ipv4_address_create(rem_addr),    : rem_port, TCPC_COMMAND_OPEN_ACTIVE, &local_conn_options);   	}   J                     J   ����   J          pr_state                     �   �     V   �  �   �          
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition                 �     �   �  m   �          
   tr_1   
       J   PKT_IN   J       ����          
    ����   
          ����                       pr_transition                 �     r   �  �   �          
   tr_2   
       ����          ����          
    ����   
          ����                       pr_transition              �       �   �  �  H          J   tr_3   J       J   TIMER_OPEN_ACTIVE   J       ����          J    ����   J          ����                       pr_transition              �       �  I  �   �          J   tr_4   J       ����          ����          J    ����   J          ����                       pr_transition                                             