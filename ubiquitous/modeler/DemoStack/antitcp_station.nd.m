MIL_3_Tfile_Hdr_ 145A 140A modeler 6 4A28B787 4A61FF8A 1A q300t wjb 0 0 none none 0 0 none 7417F960 1C75 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                     ��g�      8   <   \   `   d  ;  X  �  �  �  a  e    ����   wless_xt_rx��������                      Application Profile      traffic.Application Profile����   ����                                             count    �������    ����         ����          ����          ����           �Z             list   	�������   	����                                              �Z                        RoutingRouting Protocol      routing.Routing Protocol����    ����           ����          ����          ����                        Application Profile               Default Voice      Routing Protocol                Flood      
TIM source            none      altitude         
@       ����   
   altitude modeling            relative to subnet-platform      	condition            ����      financial cost            0.00      hostname         ����      minimized icon            circle/#708090      phase                 ����      priority              ����      role         ����      transnet.Address                     count    ���   
   ����   
      list   	���   
          
      transnet.Dest Address                     count    ���   
   ����   
      list   	���   
          
      user id              ����               �   �          
   transnet   
       
   antitcp_transnet   
          	processor                      �   �          
   routing   
       
   rte_mgr   
          	processor                      �  R          
   mac   
          sink             	processor                     �  $          
   rt_0   
       
            count    ���   
   ����   
      list   	���   
            	data rate   ���   
Ad�    ����   
   
   
          bpsk             dra_rxgroup             	dra_txdel             dra_closure             dra_chanmatch             
dra_tagain             dra_propdel             ra_tx                       nd_radio_transmitter      	     �  $          
   rr_0   
       
            count    ���   
   ����   
      list   	���   
            	data rate   ���   
Ad�    ����   
   
   
          bpsk          ?�      ����                  ����             
dra_ragain             	dra_power             dra_bkgnoise             
dra_inoise             dra_snr             dra_ber             	dra_error             dra_ecc             ra_rx                       nd_radio_receiver      
   
  �  �   
       
   a_0   
          	isotropic                  ����          @f�     ����                  ����                  ����                  ����             antenna                       
nd_antenna            �   >          
   traffic   
       
   antitcp_app   
          	processor                                  �   �  �   �   
       
   strm_0   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream                     �   �  �   �   
       
   strm_1   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream                     �    �  ,   
       
   strm_2   
       
   src stream [1]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream                     �  %  �   �   
       
   strm_3   
       
   src stream [0]   
       
   dest stream [1]   
          ����                  ����             ����                                           nd_packet_stream                
     �  )  �  �  �  �   
       
   strm_4   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream          	   
        �  �  r  �  z     
       
   strm_5   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream                     �   E  �   �   
       
   strm_6   
       
   src stream [0]   
       
   dest stream [1]   
          ����                  ����             ����                                           nd_packet_stream                     �   �  �   D   
       
   strm_7   
       
   src stream [1]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream               transnet.Load (bytes/sec)   Load (bytes/sec)           TransNet   bucket/default total/sum_time   linear   TransNet   !transnet.Traffic Sent (bytes/sec)   Traffic Sent (bytes/sec)           TransNet   bucket/default total/sum_time   linear   TransNet   %routing.Traffic Forwarded (bytes/sec)   Traffic Forwarded (bytes/sec)           Flood Routing   bucket/default total/sum_time   linear   Flood Routing   "traffic.End-to-End Delay (seconds)   End-to-End Delay (seconds)           antitcp applicaton    bucket/default total/sample mean   linear   antitcp applicaton   #traffic.Traffic Received (bits/sec)   Traffic Received (bits/sec)           antitcp applicaton   bucket/default total/sum_time   linear   antitcp applicaton   &traffic.Traffic Received (packets/sec)   Traffic Received (packets/sec)           antitcp applicaton   bucket/default total/sum_time   linear   antitcp applicaton   traffic.Traffic Received (bits)   Traffic Received (bits)           antitcp applicaton   bucket/default total/sum   linear   antitcp applicaton   "traffic.Traffic Received (packets)   Traffic Received (packets)           antitcp applicaton   bucket/default total/sum   linear   antitcp applicaton   traffic.Traffic Sent (bits/sec)   Traffic Sent (bits/sec)           antitcp applicaton   bucket/default total/sum_time   linear   antitcp applicaton   &rr_0.channel [0].throughput (bits/sec)   throughput (bits/sec)           radio receiver   bucket/default total/sum_time   linear   radio receiver   &rt_0.channel [0].throughput (bits/sec)   throughput (bits/sec)           radio transmitter   bucket/default total/sum_time   linear   radio transmitter                    