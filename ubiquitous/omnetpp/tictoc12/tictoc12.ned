simple Txc12
    gates:
        in: in[];
        out: out[];
endsimple

//
// Same as Tictoc11.
//
module Tictoc12
    submodules:
        tic: Txc12[6];   // we'll have 6 Txc modules
            display: "i=block/process";
    connections:
        tic[0].out++ --> delay 100ms --> tic[1].in++;
        tic[0].in++ <-- delay 100ms <-- tic[1].out++;

        tic[1].out++ --> delay 100ms --> tic[2].in++;
        tic[1].in++ <-- delay 100ms <-- tic[2].out++;

        tic[1].out++ --> delay 100ms --> tic[4].in++;
        tic[1].in++ <-- delay 100ms <-- tic[4].out++;

        tic[3].out++ --> delay 100ms --> tic[4].in++;
        tic[3].in++ <-- delay 100ms <-- tic[4].out++;

        tic[4].out++ --> delay 100ms --> tic[5].in++;
        tic[4].in++ <-- delay 100ms <-- tic[5].out++;
endmodule

network tictoc12 : Tictoc12
endnetwork

