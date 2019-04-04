f="out.tr"
tcp=0
udp=0
for line in open(f):
	line=line.split()
	if line[0]=='r' or line[0]=='d':
		if line[4]=="cbr":udp+=1
		elif line[4]=='tcp':tcp+=1
print('TCP:',tcp,'UDP:',udp)