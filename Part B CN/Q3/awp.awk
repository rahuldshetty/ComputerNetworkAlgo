BEGIN {
     last = 0
     tcp_sz = 0
     cbr_sz = 0
     total_sz = 0
}
{
       
   action = $1;
   time = $2;
   to = $4;
   type = $5;
   pktsize = $6;
	
	if (type == "tcp" && action == "r" && to == "3" ) 
    
                    tcp_sz += pktsize
    
	if (type == "cbr" && action == "r" && to == "3" ) 
                    cbr_sz += pktsize
    
            
  total_sz += pktsize
  
     #every second
     if (time - 1 > last) {
            last = time
            print time , (tcp_sz * 8 / 1000000 ) >>  "tcp.tr"
            print time , (cbr_sz * 8 / 1000000 ) >>  "cbr.tr"
	    print time , (total_sz * 8 / 1000000) >> "tot.tr"  
            tcp_sz = 0
            cbr_sz = 0
            total_sz = 0
     }

 }
END {
            print time , (tcp_sz * 8 / 1000000 ) >> "tcp.tr"
            print time , (cbr_sz * 8 / 1000000 ) >> "cbr.tr"
	    print time , ( total_sz * 8 / 1000000) >> "tot.tr"  
 }


