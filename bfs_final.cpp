#include<stdio.h>
#include<iostream>
#include <stdlib.h>
#include <string>
#include<queue>
#include<time.h>

using namespace std;
class Graph
{
	public:
		FILE *fptr;
		int vertexcount,visited[1000],parent1[1000],set[1000];
		int  G[1000][1000];
		int it=0;
		void init(int n);
		void BFS(int s,int g,clock_t begin);
		void path(int s,int t);
		int degree(int s);
		int* neighbours(int s);
		void addedge();
};

void Graph::init(int n)
{
	fptr = fopen("analysis_bfs.txt", "a");
	int i,j,count=0,p,k;
	vertexcount=n;
	for(i=1;i<=vertexcount;i++)
	{
		parent1[i]=0;
		for(j=1;j<=vertexcount;j++)
		{
			G[i][j]=0;
		}	
	}
	addedge();
}

void Graph::addedge()
{
	FILE *file = fopen ("Graph_data.txt", "r" );
	if ( file != NULL )
	{
		char line [ 128 ]; 
		while ( fgets ( line, sizeof line, file ) != NULL )
		{
			char u[128],v[128];
			int flag=0,k=0,l=0;
			for(int i=0;i<10;i++)
			{
				if(line[i]==' ')
					flag=1;
				if(flag!=1)
				{
					u[k]=line[i];
					k++;
				}
				else
				{
					v[l]=line[i];
					l++;
				}
			}
			G[atoi(u)][atoi(v)]=1;
			G[atoi(v)][atoi(u)]=1;
		}
		fclose (file);
	}
}

int Graph::degree(int s)
{
	int i,count=0;
	for(i=1;i<=vertexcount;i++)
	{
		if(G[s][i]==1 || G[i][s]==1)
			count=count+1;
	}
	return count;
}
int* Graph::neighbours(int s)
{

	int j=1,i;
	for(i=1;i<=vertexcount;i++)
	{
		if(G[s][i]==1)
		{		
			set[j]=	i;

			j++;
		}
	}
	return set;
}
void Graph::BFS(int s,int g,clock_t begin)
{
	fprintf(fptr,"%d ",s);
	fprintf(fptr,"%d ",g);
	int i,j,p,t,count=0,l,k;
	for(i=1;i<=vertexcount;i++)
	{
		visited[i]=0;

	}
	queue<int>q1;
	int *set1;
	i=s;
	q1.push(i);
	visited[i]=1;
	while(q1.size()>0)
	{
		t=q1.front();
		set1=neighbours(t);
		q1.pop();

		for(l=1;l<=degree(t);l++)
		{	
			if(visited[set[l]]!=1)
			{
				q1.push(set[l]);
				visited[set[l]]=1;
				parent1[set[l]]=t;			
			}

		}
	}
	path(s,g);
	clock_t end=clock();
	double ts=(double)(end-begin)/CLOCKS_PER_SEC;
	fprintf(fptr,"%lf ",ts);
	int expanded=0;
	for(int i=1;i<=89;i++)
	{
		if(visited[i]==1)
		{
			expanded++;
		}
	}
	fprintf(fptr,"%d ",expanded);
	fprintf(fptr,"%d ",it-1);
	fprintf(fptr,"\n");
}

void Graph::path(int s,int t)
{
	int k;
	if(t==s)
	{
		it=it+1;
		printf("%d",t);
		return;
	}
	else
	{
		it=it+1;
		k=parent1[t];
		path(s,k);
		printf("%c",' ');
		printf("%d",t);
	}
	//printf("It: %d\n",it)
	
}

int main()
{
	clock_t begin=clock();
	Graph G;
	int n=89,k,s,i,g;

	//FILE *fptr;
	//fptr = fopen("analysis_bfs.txt", "a");
	printf("Enter the source node\n");
	scanf("%d",&s);

	printf("Enter the destination node\n");
	scanf("%d",&g);

	G.init(n);
	G.BFS(s,g,begin);
	return 0;
}
