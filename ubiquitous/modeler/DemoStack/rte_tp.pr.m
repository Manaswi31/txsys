MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A54C186 4A620729 6 q300t wjb 0 0 none none 0 0 none 95862B1B 9AE 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                       ��g�      @   D   H      J  �  �  �     5  �  �  >           	   begsim intrpt             ����      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����             RteTransparent	\rte_instance;              #include "flood.h"       using namespace AntiTcp;       "static void message_handler(void);      !static void message_handler(void)   {   	FIN(message_handler());   	   	rte_instance.handleMessage();   	   	FOUT;   }                                           �          
   Init   
       J      //FloodRTEntry rtentry;   rte_instance.initialize();   J                     
   ����   
          pr_state        �   �          
   Wait   
                                       ����             pr_state                       K   �        �  z   �          
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition                 �     �   �  �    �   �  {   �          
   tr_1   
       ����          
   message_handler()   
       
    ����   
          ����                       pr_transition                   Traffic Forwarded (bytes/sec)           Flood Routing   bucket/default total/sum_time   linear        ԲI�%��}   -Traffic Dropped Due To Route Loop (bytes/sec)           Flood Routing   bucket/default total/sum_time   linear        ԲI�%��}          flood   oms_pr   oms_string_support              iThe transparent routing PM. It just forwards packet upward or downward transparently, doing nothing else.        