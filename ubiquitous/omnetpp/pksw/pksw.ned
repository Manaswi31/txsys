/
// $Id: pksw.ned,v 1.3 2005/11/01 06:49:38 ahmet Exp $

simple AppGen
    parameters:
        destAddresses: string,
        pkSize: numeric, 
        iaTime: numeric;
    gates:
	out: out;

endsimple

simple AppSink
    gates:
        in: in;
endsimple

simple


module Host
    submodules:

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

