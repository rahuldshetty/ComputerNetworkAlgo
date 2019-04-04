BEGIN {
     last = 0
     tcp_sz = 0
}
{
   action = $1;
   time = $2;
   to = $4;
   type = $5;
   pktsize = $6;
	
	if (type == "tcp" && action == "r" && to == "3" ) 
                    tcp_sz += pktsize
  
     #every second
     if (time - 1 > last) {
            last = time
            print time , (tcp_sz * 8 / 1000000 ) >>  "tcp.tr"
     }

 }
END {
            print time , (tcp_sz * 8 / 1000000 ) >> "tcp.tr"
 }


