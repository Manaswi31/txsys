MIL_3_Tfile_Hdr_ 145A 140A modeler 6 4A7DBBA2 4A7EF565 8 q300t wjb 0 0 none none 0 0 none 6F59196F DCE 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                       ��g�      8   <   ]   a   e   i  *  �    
  �  �    ����   wimax_ss_rtr��������                       
TIM source            none      altitude         
@       ����   
   altitude modeling            relative to subnet-platform      	condition            ����      financial cost            0.00      hostname         ����      minimized icon            circle/#708090      phase                 ����      priority              ����      role         ����      user id              ����                �   l          
   traffic   
       
   simple_source   
          	processor                   Packet Interarrival Time   ���   J   constant (5.0)   J         �   �          
   rt_0   
                   count    ���   
   ����   
      list   	���   
          
             bpsk             dra_rxgroup             	dra_txdel          
   dra_closure   
          dra_chanmatch             
dra_tagain             dra_propdel             ra_tx                       nd_radio_transmitter      	      �   �          
   rr_0   
                   count    ���   
   ����   
      list   	���   
          
             bpsk          ?�      ����                  ����             
dra_ragain             	dra_power             dra_bkgnoise             
dra_inoise             dra_snr             dra_ber             	dra_error             dra_ecc             ra_rx                       nd_radio_receiver          	   �   l          
   sink   
          sink             	processor                      �   �          
   MAC   
       
   ra_aloha_ss   
          queue                                   �   �   �   �   
       
   strm_0   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream                      �   �   �   �   
       
   strm_1   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream                      �   j   �   j   �   �   
       
   strm_2   
       
   src stream [0]   
       
   dest stream [1]   
          ����                  ����             ����                                           nd_packet_stream                	      �   �   �   i   �   i   
       
   strm_3   
       
   src stream [1]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream         	      MAC.Load(bits/sec)   Load(bits/sec)           ALOHA SS��������   ALOHA SS   MAC.Throughput(bits/sec)   Throughput(bits/sec)           ALOHA SS��������   ALOHA SS                    