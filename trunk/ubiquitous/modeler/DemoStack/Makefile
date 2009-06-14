#INC=/usr/opnet/14.5.A/sys/include
flood.ex.o: flood.ex.cpp flood.h
	op_mko -type ex -m flood
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
	-opnet_port 53275 \
	-parent_pid 17730 \
	-pipe_stdin

odb: 
	cd antitcp.project
	/usr/opnet/14.5.A/sys/pc_intel_linux/bin/op_runsim \
	    -net_name antitcp-scenario1\
	    -kernel_type development \
    -noprompt \
    -ef antitcp-scenario1-DES-1 \
    -DESinfo antitcp-scenario1-DES-1 \
	-exec_id 1 \
	-opnet_port 53275 \
	-parent_pid 17730 \
	-c \
	-debug \
	-pipe_stdin

