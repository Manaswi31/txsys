simple SimpleSource
    parameters:
	startTime: numeric,
        pkSize: numeric,
        iaTime: numeric;
    gates:
        out: out;
endsimple

simple Sink
    gates:
        in: in;
endsimple

channel physical
    delay 10ms;
    datarate 1000000;
endchannel

module sHost
    gates:
        out: out;
    submodules:
        gen: SimpleSource;
            display: "p=152,152;b=40,28";
    connections:
        gen.out --> out;
    display: "b=320,219";
endmodule

module rHost
    gates:
        in: in;
    submodules:
        sink: Sink;
            display: "p=99,48;b=40,24";
    connections:
        in --> sink.in;
    display: "b=328,211";
endmodule

module rdt_network
    submodules:
        shost: sHost;
            display: "p=90,48;i=device/pc";
        rhost: rHost;
            display: "i=device/pc;p=245,168";
    connections:
        shost.out --> physical --> rhost.in;
        rhost.out --> physical --> shost.in;
endmodule

network rdt_net : rdt_network
endnetwork



