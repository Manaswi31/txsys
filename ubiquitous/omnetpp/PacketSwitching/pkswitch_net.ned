//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2004 Andras Varga
// Copyright (C) 2005 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: pkswitch_net.ned,v 1.3 2005/11/01 06:49:38 ahmet Exp $

import "host";
import "router";

channel lanlink
    delay 0.01ms;
    datarate 100000000; // bits/sec
endchannel

channel wanlink
    delay 5ms;
    datarate 1000000; // bits/sec
endchannel

module FourHostsNet
    submodules:
        host: Host[4];
            parameters:
                address = index;
            display: "i=device/pc2";
        router: Router[2];
            parameters:
                address = index + sizeof(host);
            display: "i=abstract/router";
    connections:
        host[0].out++ --> lanlink --> router[0].in++;
        host[0].in++ <-- lanlink <-- router[0].out++;

        host[1].out++ --> lanlink --> router[0].in++;
        host[1].in++ <-- lanlink <-- router[0].out++;

        router[0].out++ --> wanlink --> router[1].in++;
        router[0].in++ <-- wanlink <-- router[1].out++;

        host[2].out++ --> lanlink --> router[1].in++;
        host[2].in++ <-- lanlink <-- router[1].out++;

        host[3].out++ --> lanlink --> router[1].in++;
        host[3].in++ <-- lanlink <-- router[1].out++;
endmodule

network pkswitch_net : 
	FourHostsNet
endnetwork

