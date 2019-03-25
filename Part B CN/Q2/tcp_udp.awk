BEGIN { 
tcp=0;
udp=0;
}
{
event = $5;
if(event=="cbr")
{
udp++;
}
if(event=="tcp")
{
tcp++;
}
}
END{
printf("No. of TCP Packets:%d\nNo.of UDP packets:%d\n",tcp,udp);
}
