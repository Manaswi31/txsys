MIL_3_Tfile_Hdr_ 145A 140A modeler 9 499E12BC 499EE6A8 B lenovo-636778b4 Administrator 0 0 none none 0 0 none 13BC2932 1099 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                  ��g�      @   D   H    �  �  �  �  �  �  �  �  �  �           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         
?�      ����   
   priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����            intrpt interval      intrpt interval����   ����       ԲI�%��}����      ԲI�%��}����      ԲI�%��}����                        /* ID of parent node */   Objid	\parent_id;           	   #include <string.h>   #include <stdio.h>       #define RADIO_INSTRM 1   #define RADIO_OUTSTRM 0       ,/* stream index for incoming interactions */   #define RTI_INSTRM	0                                                   �   �          
   init   
       J      int userid;   *parent_id = op_topo_parent (op_id_self());       :op_ima_obj_attr_get_int32 (parent_id, "user id", &userid);           if (userid==1)   	{   =	op_hla_interaction_pk_register (op_id_self (), "pos_update",   		RTI_INSTRM);   	}       J                     
   ����   
          pr_state           �          
   wait   
       
       
       
   /   *if (op_intrpt_type () == OPC_INTRPT_STRM)    {    %	if (op_intrpt_strm () == RTI_INSTRM)   	{   	    Packet * pk;   	    double posX, posY, posZ;   		   >		op_prg_odb_print_major("Received RTI interaction", OPC_NIL);       *	    /* extract information from packet */   !	    pk = op_pk_get (RTI_INSTRM);   ,	    op_pk_nfd_get_dbl (pk, "posX", & posX);   ,	    op_pk_nfd_get_dbl (pk, "posY", & posY);   ,	    op_pk_nfd_get_dbl (pk, "posZ", & posZ);   	    op_pk_destroy (pk);       3	    /* Generate packet to inform other vehicles */   *	    pk = op_pk_create_fmt ("pos_update");   +	    op_pk_nfd_set_dbl (pk, "posX",  posX);   +	    op_pk_nfd_set_dbl (pk, "posY",  posY);   +	    op_pk_nfd_set_dbl (pk, "posZ",  posZ);   $	    op_pk_send (pk, RADIO_OUTSTRM);   	}   ,	else if (op_intrpt_strm () == RADIO_INSTRM)   	{   	    Packet * pk;   	    double posX, posY, posZ;   		   ;		op_prg_odb_print_major("Received Radio packet", OPC_NIL);   		   #	    pk = op_pk_get (RADIO_INSTRM);   ,	    op_pk_nfd_get_dbl (pk, "posX", & posX);   ,	    op_pk_nfd_get_dbl (pk, "posY", & posY);   ,	    op_pk_nfd_get_dbl (pk, "posZ", & posZ);   	    op_pk_destroy (pk);       *	    pk = op_pk_create_fmt ("pos_update");   +	    op_pk_nfd_set_dbl (pk, "posX",  posX);   +	    op_pk_nfd_set_dbl (pk, "posY",  posY);   +	    op_pk_nfd_set_dbl (pk, "posZ",  posZ);   :	    op_hla_interaction_pk_send (pk, OPC_HLA_DELIVER_NOW);   	}   }   else   	{   	}       
           ����             pr_state                        �   �      �   �   �   �             tr_0          ����          ����          
    ����   
          ����                       pr_transition              5   �     #   �  H   �  H   p  $   �             tr_1          ����          ����          
    ����   
          ����                       pr_transition                                   
pos_update                              text_0          
      Register with HLA PM   
          =����             ����              ����          @b�     ����          @Y      ����          @U      ����          @D�     ����             
annot_text             Annotation Palette          ��������          ����          
@�������   
               ����              ����          ����    