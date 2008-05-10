
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

simple SwitchProc
    gates:
        in: in[];
        out: out[];
endsimple

module Host
    gates:
        out: out;
        in: in; //
                //
    submodules:
        sink: Sink;
            display: "p=83,48;i=block/sink";
        src: SimpleSource;
            display: "p=43,96;i=block/source";
        proc: HostProc;
            display: "p=86,144;i=block/process";
    connections:
        src.out --> proc.from_hl;
        sink.in <-- proc.to_hl;
        proc.to_ll --> out;
        proc.from_ll <-- in;
    display: "b=110,185";
endmodule

module Switch
    gates:
        in: in[];
        out: out[];
    submodules:
        switch_proc: SwitchProc;
            display: "p=80,48;i=block/switch";
    connections:
        in++ --> switch_proc.in++;
        out++ <-- switch_proc.out++;
    display: "b=141,89";
endmodule

module pksw
    submodules:
        host: Host[4];
            display: "p=77,88;i=device/pc2";
        switch: Switch;
            parameters:
            display: "p=122,176;i=abstract/switch";
    connections:
        host[0].out --> delay 100ms --> switch.in++;
        host[0].in <-- delay 100ms <-- switch.out++;

        host[1].out --> delay 100ms --> switch.in++;
        host[1].in <-- delay 100ms <-- switch.out++;

        host[2].out --> delay 100ms --> switch.in++;
        host[2].in <-- delay 100ms <-- switch.out++;

        host[3].out --> delay 100ms --> switch.in++;
        host[3].in <-- delay 100ms <-- switch.out++;
endmodule

network pksw_net : pksw
endnetwork

