set ns [new Simulator]
set nf [open out.nam w]
set tr [open out.tr w]
$ns namtrace-all $nf
$ns trace-all $tr

proc finish {} {
	global ns nf tr
	$ns flush-trace
	close $nf
	close $tr
	exec nam out.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]

$ns make-lan "$n0 $n1 $n2 $n3 $n4 $n5 $n6 $n7 $n8 $n9" 100Mb 10ms LL Queue/DropTail Mac/802_3

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp



set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n2 $sink1
$ns connect $tcp1 $sink1
set telnet [new Application/Telnet]
$telnet set interval_ 0.005
$telnet attach-agent $tcp1



$ns at 0.5 "$ftp start"
$ns at 4.5 "$ftp stop"
$ns at 1.0 "$telnet start"
$ns at 4.0 "$telnet stop"
$ns at 3.0 "finish"
$ns run
