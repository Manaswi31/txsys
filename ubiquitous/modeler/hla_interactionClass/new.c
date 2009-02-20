if (op_intrpt_type () == OPC_INTRPT_STRM) 
{ 
	if (op_intrpt_strm () == RTI_INSTRM)
	{
	    Packet * pk;
	    double posX, posY, posZ;

	    /* extract information from packet */
	    pk = op_pk_get (RTI_INSTRM);
	    op_pk_nfd_get_dbl (pk, "posX", & posX);
	    op_pk_nfd_get_dbl (pk, "posY", & posY);
	    op_pk_nfd_get_dbl (pk, "posZ", & posZ);
	    op_pk_destroy (pk);

	    /* Generate packet to inform other vehicles */
	    pk = op_pk_create_fmt ("pos_update");
	    op_pk_nfd_set_dbl (pk, "posX",  posX);
	    op_pk_nfd_set_dbl (pk, "posY",  posY);
	    op_pk_nfd_set_dbl (pk, "posZ",  posZ);
	    op_pk_send (pk, RADIO_OUTSTRM);
	}
	else if (op_intrpt_strm () == RADIO_INSTRM)
	{
	    Packet * pk;
	    double posX, posY, posZ;
	    pk = op_pk_get (RADIO_INSTRM);
	    op_pk_nfd_get_dbl (pk, "posX", & posX);
	    op_pk_nfd_get_dbl (pk, "posY", & posY);
	    op_pk_nfd_get_dbl (pk, "posZ", & posZ);
	    op_pk_destroy (pk);

	    pk = op_pk_create_fmt ("pos_update");
	    op_pk_nfd_set_dbl (pk, "posX",  posX);
	    op_pk_nfd_set_dbl (pk, "posY",  posY);
	    op_pk_nfd_set_dbl (pk, "posZ",  posZ);
	    op_hla_interaction_pk_send (pk, OPC_HLA_DELIVER_NOW);
	}
}

