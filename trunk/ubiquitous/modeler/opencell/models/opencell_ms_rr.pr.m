MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A1951A3 4A1A3F99 13 lenovo-636778b4 Administrator 0 0 none none 0 0 none 39C45747 1429 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                 ��g�      @   D   H    �  �  	  	  �  >  J  !  %  �           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����            begsim intrpt      begsim intrpt����   ����           ����          ����          ����                        Objid	\phy_objid;       Objid	\phy_ostrm;       Objid	\phy_istrm;          Packet*		pkptr;   double		pk_size;   double		ete_delay;      :#define CALL_REQ (op_intrpt_type()==OPC_INTRPT_REMOTE && \   $	op_intrpt_code()==User_RR_Conn_Req)          !static void call_req_handle(void)   {   	Packet *pkptr;   	       FIN(call_req_handle());       J    op_intrpt_schedule_remote (op_sim_time(), RR_Phy_Conn_Req, phy_objid);   	   	/*Create signalling packet*/   b	/*Currently I'm not sure where the RIL3 ChannReq signalling is dumped. Dump it here temporarily*/   V	pkptr = op_pk_create(Opencell_Burst_Overhead_Size_AB+Opencell_Burst_Payload_Size_AB);   	   	   	op_pk_send (pkptr, phy_ostrm);       	    FOUT;   }                                      �   �          
   Init   
       
   
   /*   stream    :  RR [0] -> phy [2]   stream    :  phy [1] -> RR [0]   */       Objid node_objid;   *node_objid = op_topo_parent(op_id_self());   Cphy_objid = op_id_frome_name (node_objid, OPC_OBJTYPE_PROC, "phy");   phy_ostrm = 0;   phy_istrm = 0;   
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
       
   call_req_handle()   
       
    ����   
          ����                       pr_transition                   End-to-End Delay (seconds)          FEnd-to-end delay of packets received by the traffic sink in this node.   Traffic Sink    bucket/default total/sample mean   linear        ԲI�%��}   Traffic Received (bits)          <Traffic received (in bits) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (bits/sec)          @Traffic received (in bits/sec) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}   Traffic Received (packets)          ?Traffic received (in packets) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (packets/sec)          CTraffic received (in packets/sec) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}      End-to-End Delay (seconds)          GEnd-to-end delay of packets received by traffic sinks across all nodes.   Traffic Sink    bucket/default total/sample mean   linear        ԲI�%��}   Traffic Received (bits)          ATraffic received (in bits) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (bits/sec)          ETraffic received (in bits/sec) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}   Traffic Received (packets)          DTraffic received (in packets) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (packets/sec)          HTraffic received (in packets/sec) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}                  General Process Description:    ----------------------------    zThe sink process model accepts packets from any number of sources and discards them regardless of their content or format.       ICI Interfaces:    --------------    None        Packet Formats:    ---------------    None        Statistic Wires:    ----------------    None        Process Registry:    -----------------    Not Applicable       Restrictions:    -------------    None        