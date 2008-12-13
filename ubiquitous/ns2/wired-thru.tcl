##################
set simDur 100.0 ;#simulation duration in seconds

set basename wired-thru

set statIntvl 1.0
set cbrIntvl 1E-3
set totalBytes 0

set val(nn)             2                         ;# number of nodes


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
for { set i 0} {$i < $val(nn)} { incr i } {
    set node_($i) [$ns node]
}

$ns duplex-link $node_(0) $node_(1) 11Mb 0.1ms DropTail

#Create a udp agent on node0
set udp0 [new Agent/UDP]
$ns attach-agent $node_(0) $udp0

# Create a CBR traffic source on node0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 1440
$cbr0 set interval_ $cbrIntvl
$cbr0 attach-agent $udp0

#Create a Null agent (a traffic sink) on node1
set sink0 [new Agent/LossMonitor]
$ns attach-agent $node_(1) $sink0

#Connet source and dest Agents
$ns connect $udp0 $sink0

proc record {} {
        global sink0 outfd totalBytes
        #Get an instance of the simulator
        set ns [Simulator instance]
        #Set the time after which the procedure should be called again
        set time 0.5
        #How many bytes have been received by the traffic sinks?
        set bytes [$sink0 set bytes_]
        set totalBytes [expr $totalBytes +$bytes]

        #Get the current time
        set now [$ns now]
        #Calculate the bandwidth (in MByte/s) and write it to the files
        puts $outfd "$now [expr $bytes/$time]"
        #Reset the bytes_ values on the traffic sinks
        $sink0 set bytes_ 0

        #Re-schedule the procedure
        $ns at [expr $now+$time] "record"
    #    puts "getting out of record()"
    #    puts "$now"
}



#a procedure to close trace file and nam file
proc finish {} {

	global ns tracefd namtracefd basename
	$ns flush-trace

	close $tracefd
	close $namtracefd
	
	exit 0
}

#
#Schedule trigger events

#Schedule events for the CBR agent that starts at 0.5s and stops at 4.5s
$ns at 10.0 "record"
$ns at 10.0 "$cbr0 start"
$ns at $simDur "$cbr0 stop"

#Call the finish procedure after 5s (of simulated time)
$ns at $simDur "finish"

#
#Run the simulation
$ns run




