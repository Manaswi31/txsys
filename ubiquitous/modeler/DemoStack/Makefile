#INC=/usr/opnet/14.5.A/sys/include
compile: antitcp.ex.cpp antitcp.h
	op_mko -type ex -m antitcp
	op_mko -type pr -m flood_rte
	op_mko -type pr -m antitcp_transnet

runsim: 
	cd antitcp.project
	/usr/opnet/14.5.A/sys/pc_intel_linux/bin/op_runsim \
	    -net_name antitcp-scenario1\
    -noprompt \
    -ef antitcp-scenario1-DES-1 \
    -DESinfo antitcp-scenario1-DES-1 \
	-exec_id 1 \
	-pipe_stdin \
	-probe antitcp-scenario1

odb: 
	cd antitcp.project
	/usr/opnet/14.5.A/sys/pc_intel_linux/bin/op_runsim \
	    -net_name antitcp-scenario1\
	    -kernel_type development \
    -noprompt \
    -ef antitcp-scenario1-DES-1 \
    -DESinfo antitcp-scenario1-DES-1 \
	-exec_id 1 \
	-c \
	-debug \
	-pipe_stdin \
	-probe antitcp-scenario1

