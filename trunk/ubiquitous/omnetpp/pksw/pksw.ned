
simple SimpleSource
    parameters:
        destAddresses: string,
        pkSize: numeric, 
        iaTime: numeric;
    gates:
	out: out;

endsimple

simple Sink
    gates:
        in: in;
endsimple

simple HostProc
    gates:
        in: from_ll;
	in: from_hl;
	out: to_ll;
	out: to_hl;
endsimple

module Host
    submodules:
	sink: Sink
	src: SimpleSource
	proc: HostProc
    gates:
	out: out;
	in: in;
    connections: 
	src.out-->proc.from_hl;
	sink.in<--proc.to_hl;
	proc.to_ll-->out;
	proc.from_ll<--in;

endmodule

module Switch
    submodules:
	switch: SwitchProc
    gates:
	in: in[];
	out: out[];
endmodule

module pksw
    submodules:
        host: Host[4];
            parameters:
                address = index;
            display: "i=device/pc2";
        switch: Switch;
            parameters:
            display: "i=abstract/switch";
    connections:
        host[0].out++ --> delay 100ms --> switch[0].in++;
        host[0].in++ <-- delay 100ms <-- switch[0].out++;

        host[1].out++ --> delay 100ms --> switch[0].in++;
        host[1].in++ <-- delay 100ms <-- switch[0].out++;

        switch[0].out++ --> delay 100ms --> switch[1].in++;
        switch[0].in++ <-- delay 100ms <-- switch[1].out++;

        host[2].out++ --> delay 100ms --> switch[1].in++;
        host[2].in++ <-- delay 100ms <-- switch[1].out++;

        host[3].out++ --> delay 100ms --> switch[1].in++;
        host[3].in++ <-- delay 100ms <-- switch[1].out++;
endmodule

network pksw_net : 
	pksw
endnetwork

