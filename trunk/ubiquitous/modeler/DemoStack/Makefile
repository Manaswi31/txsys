#INC=/usr/opnet/14.5.A/sys/include
flood.ex.o: flood.ex.cpp flood.h
	op_mko -type ex -m flood
	op_mko -type pr -m flood_rte
	op_mko -type pr -m antitcp_transnet
