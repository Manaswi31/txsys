
#illidan.modeler@gmail.com

# Initialize some parameters
Mac/802_11 set dataRate_ 11Mb
Mac/802_11 set RTSThreshold_ 3000

# ======================================================================
# Define options
# ======================================================================
set sim(end) 30.0

set val(chan)           Channel/WirelessChannel    ;# channel type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         50                         ;# max packet in ifq
set val(nn)             2                          ;# number of mobilenodes
set val(rp)             AODV                       ;# routing protocol

# ======================================================================
# Main Program
# ======================================================================


#
# Initialize Global Variables
#
set ns_		[new Simulator]
set tracefd     [open wireless.tr w]
set namfd	[open wireless.nam w]
set f0 [open wireless.data w]

$ns_ trace-all $tracefd
$ns_ namtrace-all-wireless $namfd 20 20

# set up topography object
set topo       [new Topography]

$topo load_flatgrid 20 20

#
# Create God
#
create-god $val(nn)

#
#  Create the specified number of mobilenodes [$val(nn)] and "attach" them
#  to the channel. 
#  Here two nodes are created : node(0) and node(1)

#Set Bandwidth
#$val(mac) set dataRate_ 54E6

# configure node

        $ns_ node-config -adhocRouting $val(rp) \
			 -llType $val(ll) \
			 -macType $val(mac) \
			 -ifqType $val(ifq) \
			 -ifqLen $val(ifqlen) \
			 -antType $val(ant) \
			 -propType $val(prop) \
			 -phyType $val(netif) \
			 -channelType $val(chan) \
			 -topoInstance $topo \
			 -agentTrace ON \
			 -routerTrace ON \
			 -macTrace OFF \
			 -movementTrace OFF			
			 
	for {set i 0} {$i < $val(nn) } {incr i} {
		set node_($i) [$ns_ node]	
		$node_($i) random-motion 0		;# disable random motion
	}


#
# Provide initial (X,Y, for now Z=0) co-ordinates for mobilenodes
#
$node_(0) set X_ 5.0
$node_(0) set Y_ 5.0
$node_(0) set Z_ 0.0

$node_(1) set X_ 15.0
$node_(1) set Y_ 15.0
$node_(1) set Z_ 0.0

$ns_ initial_node_pos $node_(0) 2
$ns_ initial_node_pos $node_(1) 2


# Setup traffic flow between nodes
# TCP connections between node_(0) and node_(1)
set udp [new Agent/UDP]
$udp set class_ 2
set sink [new Agent/LossMonitor]
$ns_ attach-agent $node_(0) $udp
$ns_ attach-agent $node_(1) $sink
$ns_ connect $udp $sink

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp

#800Kbps
$cbr set packetSize_ 1440 
$cbr set interval_ 0.1E-3

$ns_ at 10.0 "$cbr start" 

proc record {} {
        global sink f0 
        #Get an instance of the simulator
        set ns [Simulator instance]
        #Set the time after which the procedure should be called again
        set time 0.5
        #How many bytes have been received by the traffic sinks?
        set bytes [$sink set bytes_]
        #Get the current time
        set now [$ns now]
        #Calculate the bandwidth (in MByte/s) and write it to the files
        puts $f0 "$now [expr $bytes/$time]"
        #Reset the bytes_ values on the traffic sinks
        $sink set bytes_ 0

        #Re-schedule the procedure
        $ns at [expr $now+$time] "record"
    #    puts "getting out of record()"
    #    puts "$now"
}

#
# Tell nodes when the simulation ends
#
for {set i 0} {$i < $val(nn) } {incr i} {
    $ns_ at $sim(end) "$node_($i) reset";
}

$ns_ at $sim(end) "puts \"NS EXITING...\" "
$ns_ at $sim(end) "stop"
proc stop {} {
    global ns_ tracefd namfd f0
    $ns_ flush-trace
    close $namfd
    close $tracefd 
    exec xgraph wireless.data -geometry 800x400 &
    $ns_ halt
}

puts "Starting Simulation..."
$ns_ at 0.0 "record"
$ns_ run


