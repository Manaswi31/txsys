simple  AppGen
    parameters:
	iaTime: numberic;
    gates: 
	out: out_strm;
endsimple

simple  AppSink
    gates:
	in: in_strm;
endsimple

module sHost
    gates:
	out: out_strm;
    submodules:
	app_gen: AppGen;
    connections:
	app_gen.out_strm-->out_strm; //sHost's output port is app_gen's output port	
endmodule

module rHost
    gates:
	in: in_strm;
    submodules:
	app_sink: AppSink;
    connections:
	app_sink.in_strm-->in_strm;
endmodule


module pkcountNetwork
    submodules:
	shost: sHost;
	rhost: rHost;
	display: "i=device/pc2";
    connections:
	sHost.out_strm-->100ms-->rHost.in_strm; //currently the link delay is modeled as a constant "100ms"
endmodule
