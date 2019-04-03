#!/usr/bin/awk  -f
BEGIN {
     last = 0
     tcp_drp = 0
     cbr_drp = 0
     total_drp = 0
     tcp=0
     udp=0		
}
{
   action = $1;
   time = $2;
   type = $5;
	
	if (type == "tcp" && action == "d") 
	{
         	 tcp_drp += 1
		 tcp+=1	    	
	}
	if (type == "cbr" && action == "d") 
        {            
		cbr_drp += 1
		udp+=1    
     	}

     #every second
     if (time - 1 > last) {
            last = time
            print time , tcp_drp >> "tcpdrp.tr"
            print time , cbr_drp >> "cbrdrp.tr"
	    print time , cbr_drp + tcp_drp >> "totdrp.tr"  
            tcp_drp = 0
            cbr_drp = 0
            total_drp = 0
     }

 }
END {
            print time , tcp_drp >> "tcp.tr"
            print time , cbr_drp >> "cbr.tr"
	    print time , cbr_drp + tcp_drp >> "tot.tr" 
	printf("No. of TCP packets dropped:%d\n",tcp)
	printf("No. of UDP packets dropped:%d\n",udp)
	printf("Total packets dropped:%d\n",tcp+udp)
 
 }


