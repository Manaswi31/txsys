import "base";

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
        datalink: DataLink;
            display: "p=120,96;b=40,28";
    connections:
        gen.out --> datalink.from_hl;
        datalink.to_ll --> out;
        in --> datalink.from_ll;
    display: "b=264,139";
endmodule

module rHost
    gates:
        in: in;
        out: out;
    submodules:
        sink: Sink;
        datalink: DataLink;
            display: "p=120,96;b=40,28";
    connections:
        sink.out --> datalink.from_hl;
        datalink.to_ll --> out;
        in --> datalink.from_ll;
    display: "b=264,139";
endmodule


module sware_net
    submodules:
	shost: sHost
	rhost: rHost
    connections:
	shost.out-->physical-->rhost.in;
	rhost.out-->physical-->shost.in;

endmodule

network sware_net : sware_net
endnetwork

