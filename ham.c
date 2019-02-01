#include<stdio.h>
#define MAX 10000
#define NL printf("\n")
int n,r,data[MAX],result[MAX],temp;
char c;

void findExtraBits(){
	r=1;
	while( (1<<r) -r - 1 < n )
		r++;
}

void copy(int n,int a[],int b[]){
	for(int i=0;i<n;i++ )
		a[i]=b[i];
}

void print(int n,int a[]){
	for(int i=0;i<n;i++)printf("%d ",a[i]);
}

void findHamCode(){
	int pow=1,ptr=0;
	for(int i=1;i<=n+r;i++){
		if(pow==i)
			pow<<=1;
		else
			result[i-1]=data[ptr++];
	}
	pow=1;

	for(int j=0;j<r;j++){
		int xor=-1;
		for(int i=pow+1;i<=n+r;i++){
			int val=pow&i;
			if(val!=0){
				if(xor==-1)
					xor=result[i-1];
				else
					xor^=result[i-1];
			}
		}
		result[pow-1]=xor;
		pow<<=1;
	}
	printf("Hamming Code:");
	print(n+r,result);
	NL;

}

void findError(){
	int errorVal=0;
	int parity[r],pow=1;
	for(int j=0;j<r;j++)
	{
		int xor=data[pow-1];
		for(int i=pow+1;i<=n+r;i++){
			int val=pow&i;
			if(val==0)continue;
			else xor^=data[i-1];
		}
		parity[j]=xor;
		errorVal+=parity[j]*pow;
		pow<<=1;
		
	}

	printf("Generated Parity Bits:");
	print(r,parity);
	NL;


	if(errorVal==0)printf("All the bits are proper.\n");
	else{
		printf("Error found at bit %d\n",errorVal);
		data[errorVal-1]^=1;
		printf("Corrected bit sequence:");
		print(n+r,data);
	}

}


void main(){
	printf("**Sender**\n");
	printf("Enter no. of data bits:");
	scanf("%d",&n);
	printf("Enter data bits:");
	for(int i=0;i<n;i++)
		scanf("%d",&data[i]);
	findExtraBits();
	printf("Extra bits required to encode %d bits: %d\n",n,r);
	findHamCode();
	copy(n+r,data,result);
	
	printf("**Network**\n");
	printf("Do you want to corrupt data?(Y-Yes or N-No)");
	scanf("%d",&c);
	scanf("%c",&c);

	if(c=='Y'||c=='y')
	{
		printf("Enter bit position to corrupt:");
		scanf("%d",&temp);
		data[temp-1]^=1;
	}
	printf("**Receiver**\n");
	printf("Received data:");
	print(n+r,data);
	NL;


	findError();

}