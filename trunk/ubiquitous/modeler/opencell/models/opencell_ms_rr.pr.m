MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A1951A3 4A196C29 8 xp Administrator 0 0 none none 0 0 none D65DD75F 124B 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                               ��g�      @   D   H    �  4  /  3  
�  `  l  C  G  (           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����            begsim intrpt      begsim intrpt����   ����           ����          ����          ����                        Objid \sv_phy_objid;          Packet*		pkptr;   double		pk_size;   double		ete_delay;      :#define CALL_REQ (op_intrpt_type()==OPC_INTRPT_REMOTE && \   #	op_intrpt_code()==RR_Phy_Conn_Req)          !static void call_req_handle(void)   {       FIN(call_req_handle());       M    op_intrpt_schedule_remote (op_sim_time(), RR_Phy_Conn_Req, sv_phy_objid);       	    FOUT;   }                                      �   �          
   Init   
       
      Objid node_objid;   *node_objid = op_topo_parent(op_id_self());   Fsv_phy_objid = op_id_frome_name (node_objid, OPC_OBJTYPE_PROC, "phy");   
                     
   ����   
          pr_state           �          
   Wait   
                                       ����             pr_state                     �   �      �   �      �          
   tr_2   
       ����          ����          
    ����   
          ����                       pr_transition              �   �        �  e   �  X   P     ~          
   tr_3   
       
   CALL_REQ   
       ����          
    ����   
          ����                       pr_transition                   End-to-End Delay (seconds)          FEnd-to-end delay of packets received by the traffic sink in this node.   Traffic Sink    bucket/default total/sample mean   linear        ԲI�%��}   Traffic Received (bits)          <Traffic received (in bits) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (bits/sec)          @Traffic received (in bits/sec) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}   Traffic Received (packets)          ?Traffic received (in packets) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (packets/sec)          CTraffic received (in packets/sec) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}      End-to-End Delay (seconds)          GEnd-to-end delay of packets received by traffic sinks across all nodes.   Traffic Sink    bucket/default total/sample mean   linear        ԲI�%��}   Traffic Received (bits)          ATraffic received (in bits) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (bits/sec)          ETraffic received (in bits/sec) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}   Traffic Received (packets)          DTraffic received (in packets) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (packets/sec)          HTraffic received (in packets/sec) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}                  General Process Description:    ----------------------------    zThe sink process model accepts packets from any number of sources and discards them regardless of their content or format.       ICI Interfaces:    --------------    None        Packet Formats:    ---------------    None        Statistic Wires:    ----------------    None        Process Registry:    -----------------    Not Applicable       Restrictions:    -------------    None        