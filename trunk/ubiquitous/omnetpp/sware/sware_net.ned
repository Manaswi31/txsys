import
    "base";

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

simple DataLink
    gates:
        in: from_hl;
        in: from_ll;
        out: to_hl;
        out: to_ll;
endsimple

