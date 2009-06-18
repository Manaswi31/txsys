MIL_3_Tfile_Hdr_ 145A 140A modeler 9 4A373895 4A39B772 12 lenovo-636778b4 Administrator 0 0 none none 0 0 none A13006AB 26D8 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                 ��g�      @  A  E      �  �     �   �   �  $�  $�  �      Packet Interarrival Time   �������      seconds   �      constant (1.0)      ����      ����         bernoulli (mean)      bernoulli (mean)      $binomial (num_samples, success_prob)      $binomial (num_samples, success_prob)      chi_square (mean)      chi_square (mean)      constant (mean)      constant (mean)      erlang (scale, shape)      erlang (scale, shape)      exponential (mean)      exponential (mean)      extreme (location, scale)      extreme (location, scale)      fast_normal (mean, variance)      fast_normal (mean, variance)      gamma (scale, shape)      gamma (scale, shape)      geometric (success_prob)      geometric (success_prob)      laplace (mean, scale)      laplace (mean, scale)      logistic (mean, scale)      logistic (mean, scale)      lognormal (mean, variance)      lognormal (mean, variance)      normal (mean, variance)      normal (mean, variance)      pareto (location, shape)      pareto (location, shape)      poisson (mean)      poisson (mean)      power function (shape, scale)      power function (shape, scale)      rayleigh (mean)      rayleigh (mean)      triangular (min, max)      triangular (min, max)      uniform (min, max)      uniform (min, max)      uniform_int (min, max)      uniform_int (min, max)      weibull (shape, scale)      weibull (shape, scale)      scripted (filename)      scripted (filename)         �Specifies the distribution name and arguments to be used for generating random outcomes for times between successive packet generations.       �While selecting a distribution, replace the arguments within parenthesis (e.g., mean, variance, location, etc.) with the desired numerical values.       �For the special "scripted" distribution, specify a filename (*.csv or *.gdf) containing the values required as outcomes. Values will be picked from this file in cyclic order.   oms_dist_configure    oms_dist_conf_dbox_click_handler   $oms_dist_conf_dbox_new_value_handler���������Z             Packet Size   �������      bits   �      constant (1024)      ����      ����         bernoulli (mean)      bernoulli (mean)      $binomial (num_samples, success_prob)      $binomial (num_samples, success_prob)      chi_square (mean)      chi_square (mean)      constant (mean)      constant (mean)      erlang (scale, shape)      erlang (scale, shape)      exponential (mean)      exponential (mean)      extreme (location, scale)      extreme (location, scale)      fast_normal (mean, variance)      fast_normal (mean, variance)      gamma (scale, shape)      gamma (scale, shape)      geometric (success_prob)      geometric (success_prob)      laplace (mean, scale)      laplace (mean, scale)      logistic (mean, scale)      logistic (mean, scale)      lognormal (mean, variance)      lognormal (mean, variance)      normal (mean, variance)      normal (mean, variance)      pareto (location, shape)      pareto (location, shape)      poisson (mean)      poisson (mean)      power function (shape, scale)      power function (shape, scale)      rayleigh (mean)      rayleigh (mean)      triangular (min, max)      triangular (min, max)      uniform (min, max)      uniform (min, max)      uniform_int (min, max)      uniform_int (min, max)      weibull (shape, scale)      weibull (shape, scale)      scripted (filename)      scripted (filename)      None      None         �Specifies the distribution name and arguments to be used for generating random outcomes for the size of generated packets (specified in bits).       �While selecting a distribution, replace the arguments within parenthesis (e.g., mean, variance, location, etc.) with the desired numerical values.       �For the special "scripted" distribution, specify a filename (*.csv or *.gdf) containing the values required as outcomes. Values will be picked from this file in cyclic order.   oms_dist_configure    oms_dist_conf_dbox_click_handler   $oms_dist_conf_dbox_new_value_handler���������Z             
Start Time   �������      secs      @$         10.0              ����              ����         10.0   @$      ����      Infinity   ��      ����         �Specifies the simulation time in seconds when the source will start its traffic generation. Setting the value to "Infinity" will simply disable the source. �Z             	Stop Time   �������      secs      ��         Infinity              ����              ����         Infinity   ��      ����         �Specifies the simulation time in seconds when the source will stop its traffic generation. Setting the value to "Infinity" will make the source generate traffic until the end of the simulation.�Z                 	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����             Application	\app_instance;                  +/* Variables used in state transitions.		*/   int			intrpt_code;      #include "flood.h"       using namespace AntiTcp;           /* Function prototypes.				*/   (static void			ss_packet_generate (void);      static void   ss_packet_generate (void)   	{       	FIN(ss_packet_generate());   	   	app_instance.genPk();   	   	FOUT;   	   	}	                                        \   Y          
   init   
       
      app_instance.initialize();   
       
      F/* Determine the code of the interrupt, which is used in evaluating	*/   +/* state transition conditions.										*/    intrpt_code = op_intrpt_code ();   
           ����             pr_state        J   Z          
   generate   
       J      app_instance.scheduleNextPk();       J       
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