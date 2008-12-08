##################
set simDur 60.0

set basename lan

set statIntvl 1.0
set cbrIntvl 1.0

set val(bw)		100Mb
set val(delay)		0.1ms
set val(mac)            Mac/802_3                 ;# MAC type
set val(ifq)            Queue/DropTail    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(nn)  8 ;#number of nodes in the LAN


###################
#Initialize and create output files
#Create a simulator instance
set ns [new Simulator]

#Crate a trace file and animation record
set tracefd [open $basename.tr w]
$ns trace-all $tracefd
set namtracefd [open $basename.nam w]
$ns namtrace-all $namtracefd

set outfd [open $basename.out w]

#######################
#Create Topology


for {set i 0} {$i < $val(nn) } {incr i} {
	set node($i) [$ns node]
	lappend nodelist $node($i)
}

$ns make-lan $nodelist $val(bw) $val(delay) $val(ll) $val(ifq) $val(mac)

set node_ex [$ns node]

#$ns duplex-link $node_ex $node(0) 100Mb 0.1ms DropTail
#$ns duplex-link-op $node_ex $node(0) orient right

#Create a udp agent on node0
set udp0 [new Agent/UDP]
$ns attach-agent $node(0) $udp0

# Create a CBR traffic source on node0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ $cbrIntvl
$cbr0 set random_ 1
$cbr0 attach-agent $udp0

#Create a Null agent (a traffic sink) on node1
set sink0 [new Agent/LossMonitor]
$ns attach-agent $node(7) $sink0

#Connet source and dest Agents
$ns connect $udp0 $sink0

proc record {} {
    global sink0 ns outfd statIntvl
    set bytes [$sink0 set bytes_]
    set now [$ns now]
    puts $outfd "$now $bytes"
    $sink0 set bytes_ 0
    $ns at [expr $now+$statIntvl] "record"
}

#a procedure to close trace file and nam file
proc finish {} {

	global ns tracefd namtracefd basename
	$ns flush-trace

	close $tracefd
	close $namtracefd
	
	exec nam $basename.nam &
	exit 0
}

#
#Schedule trigger events

#Schedule events for the CBR agent that starts at 0.5s and stops at 4.5s
$ns at 0.5 "record"
$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

#Call the finish procedure after 5s (of simulated time)
$ns at $simDur "finish"

#
#Run the simulation
$ns run




