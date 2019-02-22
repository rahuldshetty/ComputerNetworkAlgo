#include<stdio.h>
#define MAX 10000
#define INF 999
#define Entry struct entry
#define SEPLINE printf("\n******************\n")

Entry{
	int out;
	int cost;
};

int n,temp,ch,src,dest;
Entry table[MAX][MAX];

void read_table(){
	printf("**Enter 999 to show no direct path**\n");
	for(int i=0;i<n;i++)
	{
		printf("Enter details of router %c\n", 'A'+i );
		for(int j=0;j<n;j++)
		{
			if(i==j)
			{
				table[i][j].cost=0;
				table[i][j].out=i;
			}
			else{
				printf("Enter cost to reach %c :",'A' + j );
				scanf("%d",&temp);
				table[i][j].cost=temp;
				if(temp!=INF)
					table[i][j].out=j;
			}
		}
		SEPLINE;

	}

}

void buildTable(){
	for(int src=0;src<n;src++)
		for(int inter=0;inter<n;inter++)
			for(int dest=0;dest<n;dest++)
			{
				if(src!=dest && table[src][inter].cost!=INF && table[inter][dest].cost!=INF)
				{
					int newCost = table[src][inter].cost + table[inter][dest].cost;
					if(table[src][dest].cost > newCost)
					{
						table[src][dest].cost=newCost;
						table[src][dest].out=inter;
					}

				}
			}
}

void printTable(){
	for(int i=0;i<n;i++)
	{
		printf("Routing table for router %c\n",i+'A' );
		printf("Router\tOutLine\tCost\n");
		for(int j=0;j<n;j++)
		{
			printf("%c\t%c\t%d\n",'A'+j,table[i][j].out+'A',table[i][j].cost);
		}
		SEPLINE;

	}
}

void findPath(int a,int b)
{
	if(a==b)
	{
		printf(" %c\n",a+'A');
		return;
	}
	printf(" %c -> ",a+'A');
	findPath(table[a][b].out,b);
}

int main()
{
	printf("Enter no. of routers:\n");
	scanf("%d",&n);

	read_table();

	buildTable();

	printTable();

	do{
		printf("1.Search Path\t2.Quit\nEnter option:");
		scanf("%d",&ch);
		if(ch!=1)
			break;
		else{
			SEPLINE;
			printf("Enter source,destination routers:\n" );
			scanf("%s %s",&src,&dest);
			src-='A';
			dest-='A';
			if(table[src][dest].cost==INF)
				printf("No Path exits...\n" );
			else{
				printf("Path:\n");
				findPath(src,dest);
				printf("Path Cost: %d\n",table[src][dest].cost );
			}
		}
	}while(1);


}