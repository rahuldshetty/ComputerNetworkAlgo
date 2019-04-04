BEGIN { 
tcp=0;
udp=0;
}
{
event = $5; action=$1;
if(event=="cbr" && ( action=="r" || action=="d" ) )
{
udp++;
}
if(event=="tcp" && ( action=="r" || action=="d" ))
{
tcp++;
}
}
END{
printf("No. of TCP Packets:%d\nNo.of UDP packets:%d\n",tcp,udp);
}
