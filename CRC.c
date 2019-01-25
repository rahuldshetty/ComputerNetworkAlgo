#include<stdio.h>
#define MAX 10000

int n,input[MAX],reg[16],pos;
char ch;

void findCRC(){
	for(int i=0;i<16;i++)reg[i]=0;
	int feedback;
	for(int i=0;i<n+16;i++)
	{
		feedback=reg[15];
		for(int j=15;j>0;j--)
			reg[j]=reg[j-1];
		reg[0]=input[i];
		if(feedback)
		{
			reg[12]^=1;
			reg[5]^=1;
			reg[0]^=1;
		}
	}
	printf("\nRegister Contents:");
	for(int i=15;i>=0;i--)printf("%d ",reg[i]);
	for(int i=n,j=15;j>=0;i++,j--)
		input[i]=reg[j];
}

void printCRC(){
	printf("\nCRC CODE:");
	for(int i=0;i<n+16;i++)
		printf("%d ",input[i]);
}

void findError(){
	int found=-1;
	int count=0;
	for(int i=15;i>=0;i--)
	{
		if(reg[i]==1)
		{
			found=i;
			break;
		}
		count++;
	}
	if(found!=-1)
	{
		printf("\nBit corrupted at position:%d\n",found);
	}
	else{
		printf("\nReceived data is error free.\n");		
	}

}

void main(){
	printf("Sender:\n");
	printf("Enter no. of data bits:");
	scanf("%d",&n);
	printf("Enter data bits(0,1):");
	for(int i=0;i<n;i++)
		scanf("%d",&input[i]);
	for(int i=n;i<n+16;i++)input[i]=0;

	findCRC();
	printCRC();

	printf("\nNetowrk:\n");
	printf("Do you want to corrupt data(Yes-Y No-N):");
	scanf("%s",&ch);
	if(ch=='y'||ch=='Y'){
		printf("Enter position to corrupt:");
		scanf("%d",&pos);
		input[n+15-pos]=(input[n+15-pos]==1?0:1);
	}
	printf("\nReciever:\n");
	
	printf("Recieved data:\n");
	for(int i=0;i<n+16;i++)printf("%d ", input[i] );

	findCRC();
	printCRC();
	findError();
}