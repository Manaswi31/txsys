MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A373895 4A6322F5 1A q300t wjb 0 0 none none 0 0 none 3A28F8B3 1863 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                     ��g�      @  �  �  �  �  U  {  �      L  [  _  I      Application Profile   �������   ����             Default Voice                             Default Voice               count    ���   
   ����   
      list   	���   
          
      Off               count    ���   
   ����   
      list   	���   
            
Start Time   ���   
��         Infinity   
   
          count    �������    ����         ����          ����          ����           �Z             list   	�������   	����                                               Packet Size   �������      bits         constant (260)      ����      ����           �Z             Packet Interarrival Time   �������      seconds         constant(0.02)      ����      ����           �Z             
Start Time   �������      seconds      @$      ����              ����              ����         10   @$      ����      Infinity   ��      ����       �Z             	Stop Time   �������      seconds      ��         Infinity              ����              ����         Infinity   ��      ����       �Z          �Z          �Z                 	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����             Application	\app_instance;                  +/* Variables used in state transitions.		*/   int			intrpt_code;      #include "antitcp.h"       using namespace AntiTcp;           /* Function prototypes.				*/   (static void			ss_packet_generate (void);      static void   ss_packet_generate (void)   	{       	FIN(ss_packet_generate());   	   	app_instance.genPk();   	   	FOUT;   	   	}	                                        \   Y          
   init   
       
      app_instance.initialize();   
       
      F/* Determine the code of the interrupt, which is used in evaluating	*/   +/* state transition conditions.										*/    intrpt_code = op_intrpt_code ();   
           ����             pr_state        J   Z          
   generate   
       
      app_instance.scheduleNextPk();       
       
      F/* Determine the code of the interrupt, which is used in evaluating	*/   +/* state transition conditions.										*/    intrpt_code = op_intrpt_code ();       
           ����             pr_state        J            
   stop   
       
      app_instance.finalize();       
                         ����             pr_state                        �   O      x   X  .   Y          
   tr_0   
       
   START   
       
   ss_packet_generate()   
       
   ����   
          ����                       pr_transition                �   �      o   m  5   �          
   tr_1   
       
   DISABLED   
       ����          
   ����   
          ����                       pr_transition              d   �     I   u  I   �          
   tr_2   
       
   STOP   
       ����          
   ����   
          ����                       pr_transition              �   X     `   k  y   �  y   (  ^   E          
   tr_3   
       
   PACKET_GENERATE   
       
   ss_packet_generate()   
       
   ����   
          ����                       pr_transition               antitcp_app_sink      Packet Interarrival Time (secs)          &The time interval in seconds that is     "separating successive arrivals of    !packets produced by this source.        antitcp applicaton    bucket/default total/sample mean   linear        ԲI�%��}   Packet Size (bits)          'Size of the packets that are generated    by this source.       antitcp applicaton    bucket/default total/sample mean   linear        ԲI�%��}   Traffic Sent (bits/sec)          'Total size of packets in bits that are    %generated and sent to lower layer by    this source in one second.       antitcp applicaton   bucket/default total/sum_time   linear        ԲI�%��}   Traffic Sent (packets/sec)          (Total number of packets per second that    &are generated and sent to lower layer    by this source.        antitcp applicaton   bucket/default total/sum_time   linear        ԲI�%��}          oms_dist_support   oms_string_support              General Process Description:    ----------------------------       �The simple_source process model is implemented to replace "ideal source" module type, which is not supported starting with OPNET 7.0 release. The model simply generates packets and forwards them to lower layer.  Interarrival time, size and format of the packets are determined based on the model attribute values. Similarly simulation times when the process will start and stop its packet generation activities are also determined by user specifications via model attributes.               Packet Formats:   ---------------       =Unformatted or formatted packets based on user configuration.                ICI Interfaces:    ---------------       3The simple_source model does not use any ICI model.               Restrictions:   -------------        �* Connection with the lower layer is hardcoded as "Stream 0" in the header block under the constant definition for SSC_STRM_TO_LOW.       =* This model is not implemented to handle any packet arrival.        