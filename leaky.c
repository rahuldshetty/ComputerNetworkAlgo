#include<stdio.h>
#include<stdlib.h>
#define MAX 1000
#define packet struct Packet
packet{
	int time,size;
}packets[MAX];
int n;

void readPackets(){
	for(int i=0;i<n;i++)
	{
		printf("\nEnter arrival time,size of packet %d:",i+1);
		scanf("%d%d",&packets[i].time,&packets[i].size);
	}
}

void leakyBucket(int bucketSize,int time,int size)
{
	int capacity=0;
	int j=0,i;
	for(i=0;i<=30;i++)
	{
		if(packets[j].time==i)
		{
			if(capacity+packets[j].size<=bucketSize)
			{
				capacity+=packets[j].size;
				printf("\nAt time=%d inserted packet %d with size %d\n",i,j+1,packets[j].size);
				printf("Free Bucket Space=%d\n",bucketSize-capacity);

			}
			else{
				printf("\nAt time=%d packet %d discarded\n",i,j+1);
			}
			j++;
		}
		if((i%time)==0 && capacity>0)
		{
			int out=(capacity>=size)?size:capacity;
			capacity-=out;
			printf("\nAt time=%d , %d KB transferred.\n",i,out);
			printf("Free Bucket Space=%d\n",bucketSize-capacity);

		}
	}
	while(capacity!=0)
	{
		int out=(capacity>=size)?size:capacity;
		capacity-=out;
		printf("\nAt time=%d , %d KB transferred.\n",i,out);
		printf("Free Bucket Space=%d\n",bucketSize-capacity);		
		i+=1;
	}
	printf("Bucket Empty.\n");

}

void main(){
	int b,t,s;
	printf("Enter no. of packets:");
	scanf("%d",&n);
	readPackets();
	printf("Enter bucket size,time,rate:");
	scanf("%d%d%d",&b,&t,&s);
	leakyBucket(b,t,s);

}