MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A151648 4A1E951C F lenovo-636778b4 Administrator 0 0 none none 0 0 none C584BAF0 8D5 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                   ��g�      @   D   H      6  �  �  �  �  �  �  �  *           	   begsim intrpt             ����      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����             )Opencell_Phy_Mod_Data*	\phy_mod_data_ptr;              (#include "../include/opencell_support.h"      static void init(void)   	{   	FIN(init());   D	phy_mod_data_ptr = (Opencell_Phy_Mod_Data*) op_pro_modmem_access();   	   	FOUT;   	}       static void xmt(void)   	{   	Packet* pkptr;   	   	FIN(xmt());   	   V	pkptr = op_pk_create(Opencell_Burst_Overhead_Size_AB+Opencell_Burst_Payload_Size_AB);   	   0	op_pk_send (pkptr, phy_mod_data_ptr->tx_ostrm);   	   	FOUT;   	   	   	   	}                                            �          
   Init   
       
      init();   
                     
   ����   
          pr_state        �   �          
   Xmit   
                                       ����             pr_state                       i   �        �  �   �          
   tr_0   
       ����          
   xmt()   
       
    ����   
          ����                       pr_transition              $   �     �   �  �  $     �  �   �          
   tr_1   
       ����          
   xmt()   
       
    ����   
          ����                       pr_transition                                             