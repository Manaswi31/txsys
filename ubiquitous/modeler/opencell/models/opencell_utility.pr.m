MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A18B53A 4A1E97F7 C lenovo-636778b4 Administrator 0 0 none none 0 0 none D1BC476D 782 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                   ��g�      @   D   H      �  3  7  ;  ?  v  z  ~  w           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����                     (#include "../include/opencell_support.h"   %Opencell_Global_Share * global_share;      static void init(void)   {       FIN(init());   @    global_share = (Opencell_Global_Share*) opencell_mem_alloc (   %	    sizeof (Opencell_Global_Share));   (    global_share->start_of_epoch = 10.0;           	    FOUT;   }                                               �          
   Init   
       
      init();   
                     
   ����   
          pr_state        �   �          
   Wait   
                                       ����             pr_state                     L   �        �  �   �          
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition                           oms_pr   opencell_support   	simulator                    