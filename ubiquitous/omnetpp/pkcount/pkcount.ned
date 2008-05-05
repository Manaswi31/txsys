simple AppGen
    parameters:
        iaTime: numeric;

    gates:
        out: out_strm;
endsimple

simple AppSink
    gates:
        in: in_strm;
endsimple

module sHost
    gates:
        out: out_strm;
    submodules:
        app_gen: AppGen;
            display: "p=181,48;b=40,24";
    connections:
        app_gen.out_strm --> out_strm; //sHost's output port is app_gen's output port	
endmodule

module rHost
    gates:
        in: in_strm;
    submodules:
        app_sink: AppSink;
    connections:
        app_sink.in_strm <-- in_strm;
endmodule


module pkcountNetwork
    submodules:
        shost: sHost;
            display: "p=123,48;i=device/pc";
        rhost: rHost;
            display: "i=device/pc2";
    connections:
        shost.out_strm --> delay 100ms --> rhost.in_strm;
                                                          //currently the link delay is modeled as a constant "100ms"

endmodule

network pkcount : pkcountNetwork
endnetwork

