//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2004 Andras Varga
// Copyright (C) 2005 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: host.ned,v 1.5 2007/05/13 11:07:28 ahmet Exp $

import
    "modules";

module Host
    parameters:
        address: numeric,
        destAddressList: string; // list of destination host addresses,
                                 // separated by space. E.g. "1 3 9"
    gates:
        in: in[];
        out: out[];
    submodules:
        app_gen: AppGen;
            parameters:
                destAddresses = destAddressList;
            display: "p=82,88;i=block/source";
        app_sink: AppSink;
            display: "p=160,88;i=block/sink";
        network_layer: NetworkLayer;
            gatesizes:
                in[sizeof(in)],
                out[sizeof(out)];
            display: "p=117,168;i=block/switch";
        pk_queue: PDropTailQueue[sizeof(out)];
            display: "p=55,224;i=block/passiveq;q=packet_queue";
        server: Server[sizeof(out)];
            display: "p=51,300,c,60;i=block/server";
    connections:
        network_layer.localOut --> app_sink.in;
        network_layer.localIn <-- app_gen.out;
        for i=0..sizeof(in)-1 do
            network_layer.out[i] --> pk_queue[i].in;
            pk_queue[i].out --> server[i].in;
            server[i].out --> out[i] display "m=s";
            network_layer.in[i] <-- in[i] display "m=s";
        endfor;
endmodule

