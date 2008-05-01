//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2004 Andras Varga
// Copyright (C) 2005 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: router.ned,v 1.2 2007/05/13 11:07:28 ahmet Exp $

import
    "modules";

module Router
    parameters:
        address: numeric;
    gates:
        in: in[];
        out: out[];
    submodules:
        network_layer: NetworkLayer;
            gatesizes:
                in[sizeof(in)],
                out[sizeof(out)];
	    // See Section 9.1.2 (Submodule display strings) of the user manual
	    // for details on the use of display strings.
            display: "p=70,96;i=block/switch";
        pk_queue: PDropTailQueue[sizeof(out)];
            display: "p=170,36,column,60;i=block/passiveq;q=packet_queue";
        server: Server[sizeof(out)];
            display: "p=270,36,column,60;i=block/server";
    connections nocheck:
        for i=0..sizeof(in)-1 do
            network_layer.out[i] --> pk_queue[i].in;
            pk_queue[i].out --> server[i].in;
            server[i].out --> out[i] display "m=e";
            network_layer.in[i] <-- in[i] display "m=w,,,48,0";
        endfor;
    display: "b=328,186";
endmodule

