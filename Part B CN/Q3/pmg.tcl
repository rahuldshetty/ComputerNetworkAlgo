set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}

$ns color 1 Blue
$ns color 2 Red

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n2 $n1 5Mb 5ms DropTail
$ns duplex-link $n1 $n3 3Mb 8ms DropTail

$ns duplex-link-op $n0 $n1 orient right-down
$ns duplex-link-op $n2 $n1 orient right-up
$ns duplex-link-op $n1 $n3 orient right

set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1
set ftp [new Application/FTP]
$ftp attach-agent $tcp1

set tcp2 [new Agent/TCP]
$ns attach-agent $n2 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2
$ns connect $tcp2 $sink2
$tcp2 set fid_ 2
set telnet [new Application/Telnet]
$telnet set interval_ 0.005
$telnet attach-agent $tcp2

$ns at 1.0 "$ftp start"
$ns at 4.5 "$ftp stop"
$ns at 0.5 "$telnet start"
$ns at 4.0 "$telnet stop"
$ns at 5.0 "finish"
$ns run


