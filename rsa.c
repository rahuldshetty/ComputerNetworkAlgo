#include<stdio.h>
#define ull unsigned long long
#define MAX 9999

ull p,q,n,e,z,d;
ull C[MAX],D[MAX];
char msg[MAX];
ull gcd(ull a,ull b)
{
	return (b==0) ? a : gcd( b , a%b );
}

int checkRelative(ull a,ull b)
{
	return gcd(a,b)==1? 1 : 0 ;
}

ull modPower(ull a,ull b,ull tn)
{
	if(b==0)return 1;
	if(b==1)return a%tn;
	else if(b%2==0)
	{
		ull temp=modPower(a,b/2,tn)%tn;
		return (temp*temp)%tn;
	}
	else{
		ull temp=modPower(a,b-1,n)%tn;
		return (temp * a % tn) % tn ;
	}
}

void computeRSA(){
	n=p*q;
	z=(p-1)*(q-1);
	for(ull tempE=z-1;tempE>=2;tempE--)
	{
		if(checkRelative(tempE,z))
		{
			int found=0;
			e=tempE;		
			for(ull tempD=1;tempD<=n && tempD!=e;tempD++)
			{
				ull mul=(tempD%z * e % z) % z;
				if(mul==1)
				{	
					d=tempD;
					found=1;
					break;
				}
			}
			if(found)
				break;
			
		}

	}
	printf("Parameters:\n");
	printf("N:%llu\tZ:%llu\tE:%llu\tD:%llu\n",n,z,e,d);
}

void printArray(ull d[],int size)
{
	for(int i=0;i<size;i++)
		printf("%c",(int)d[i]);
	printf("\n");
}

void main(){
	printf("Enter two large prime numbers:");
	scanf("%llu%llu",&p,&q);

	computeRSA();

	printf("Public Key:{%llu,%llu}\n",e,n);
	printf("Private Key:{%llu,%llu}\n",d,n);

	printf("Enter plain text to encrypt:");
	scanf("%d",msg);
	scanf("%[^\n]",msg);
	
	int i,count=0;

	for(i=0;msg[i]!='\0';i++){
		int P = (int)(msg[i]);
		C[i]=(int)modPower(P,e,n)%n;
		count++;			
	}

	printf("Encrypted message:\n");
	printArray(C,count);

	for(i=0;C[i]!='\0';i++)
	{
		ull c = (int)C[i];
		D[i] = (char)((int)modPower(c,d,n)%n);
	}

	printf("Decrypted message:\n");
	printArray(D,count);
}