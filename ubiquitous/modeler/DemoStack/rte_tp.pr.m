MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A54C186 4A631FD3 7 q300t wjb 0 0 none none 0 0 none 8D2965BA 985 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                       ��g�      @   D   H      J  �  �  �       }  �  >           	   begsim intrpt             ����      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����             RteTransparent	\rte_instance;              #include "flood.h"       using namespace AntiTcp;       "static void message_handler(void);      !static void message_handler(void)   {   	FIN(message_handler());   	   	rte_instance.handleMessage();   	   	FOUT;   }                                           �          
   Init   
       
      //FloodRTEntry rtentry;   rte_instance.initialize();   
                     
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
          ����                       pr_transition                   Traffic Forwarded (bytes/sec)           Flood Routing   bucket/default total/sum_time   linear        ԲI�%��}   -Traffic Dropped Due To Route Loop (bytes/sec)           Flood Routing   bucket/default total/sum_time   linear        ԲI�%��}                      iThe transparent routing PM. It just forwards packet upward or downward transparently, doing nothing else.        