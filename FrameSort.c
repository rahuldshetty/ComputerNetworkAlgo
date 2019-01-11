#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include<string.h>
#define MAX 10000
#define FSIZE 3
#define Frame struct frame

Frame{
	int no;
	char data[MAX];	
};

char msg[MAX],temp[MAX];
int ch,nf,len;
Frame *orig,*tempf;

Frame* createFrames(Frame *f,int size){
	f=(Frame*)malloc(sizeof(Frame)*size);
	return f;	
}

void divide()
{
	len=strlen(msg);
	nf=len/FSIZE + (len%FSIZE!=0? 1 : 0 ) ;
	orig=createFrames(orig,nf);
	int start=0,end=FSIZE;
	for(int i=0;i<nf;i++)
	{
		orig[i].no=i;
		for(int j=start;j<end;j++)
			orig[i].data[j%FSIZE]=msg[j];
		start=end;
		end = end > len ? (len):(end+FSIZE);
	}
	
}

void printFrames(Frame *f,int size){
	for(int i=0;i<size;i++)
		printf("Frame No:%d\tData:%s\n",f[i].no,f[i].data);
}

void askUserFrames(){
	printf("Enter no. of Frames:");
	scanf("%d",&nf);
	orig=createFrames(orig,nf);
	for(int i=0;i<nf;i++)
	{
		orig[i].no=i;
		printf("Enter details of frame%d:",i+1);
		scanf("%s",temp);
		strcpy(orig[i].data,temp);
	}
}

void sort(){
	for(int i=0;i<nf;i++)
	{
		int min=i;
		for(int j=i+1;j<nf;j++)
			if(orig[min].no > orig[j].no )
				min=j;
		Frame t=orig[i];
		orig[i]=orig[min];
		orig[min]=t;	
	}	
}

void randomize(){
	srand(time(NULL));
	for(int j=nf-1;j>0;j--)
	{
		int r=rand()%(j+1);
		Frame t=orig[r];
		orig[r]=orig[j];
		orig[j]=t;
	}
}

void askUserInput(){
	tempf=(Frame*)malloc(sizeof(Frame)*nf);
	printf("Enter shuffled sequence:");
	for(int i=0;i<nf;i++)
	{
		scanf("%d",&ch);
		tempf[ch-1]=orig[i];
	}
	orig=tempf;		
}

void displayMsg()
{
	printf("\nOriginal Message:\n");
	for(int i=0;i<nf;i++)
	{
		printf("%s",orig[i].data);
	}
	
}

void main(){
	printf("1.Enter String\t2.Enter no. of frames\nEnter option:");
	scanf("%d",&ch);
	
	switch(ch)
	{
		
		case 1:
			//Ask user for single String.
			printf("Enter complete message:");
			scanf("%s",msg);
			divide();									
			break;
		case 2:
			//Ask user for each Frame.
			askUserFrames();			
			break;
	}
	printf("\nFrames Information:\n");
	printFrames(orig,nf);
	
	printf("\n1.Random Shuffle\t2.User Input Sequence\nEnter option:");
	scanf("%d",&ch);
	
	switch(ch)
	{
		case 1:
			randomize();
			break;		
		case 2:
			askUserInput();
			break;
	}	
	printf("\nShuffled Frames:\n");
	printFrames(orig,nf);
	
	sort();
	
	printf("\nSorted Frames:\n");
	printFrames(orig,nf);
	
	displayMsg();

	
}
