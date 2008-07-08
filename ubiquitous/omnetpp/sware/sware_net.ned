import
    "base";

channel physical
    delay 0.01ms;
    datarate 1000000;
endchannel

simple DataLink
    gates:
        in: from_hl;
        in: from_ll;
        out: to_hl;
        out: to_ll;
endsimple

module sHost
    gates:
        in: in;
        out: out;
    submodules:
        gen: SimpleSource;
        sink: Sink;
        datalink: DataLink;
            display: "p=152,152;b=40,28";
    connections:
        gen.out --> datalink.from_hl;
        datalink.to_ll --> out;
        datalink.to_hl --> sink.in;
        in --> datalink.from_ll;
    display: "b=320,219";
endmodule

module rHost
    gates:
        in: in;
        out: out;
    submodules:
        gen: SimpleSource;
            display: "p=196,56;b=40,24";
        sink: Sink;
            display: "p=99,48;b=40,24";
        datalink: DataLink;
            display: "p=160,144;b=40,28";
    connections:
        datalink.to_hl --> sink.in;
        datalink.to_ll --> out;
        gen.out --> datalink.from_hl;
        in --> datalink.from_ll;
    display: "b=328,211";
endmodule


module sware_net
    submodules:
        shost: sHost;
            display: "p=90,48;i=device/pc";
        rhost: rHost;
            display: "i=device/pc;p=245,168";
    connections:
        shost.out --> physical --> rhost.in;
        rhost.out --> physical --> shost.in;

    display: "b=291,218";
endmodule

network sware_net : sware_net
endnetwork

