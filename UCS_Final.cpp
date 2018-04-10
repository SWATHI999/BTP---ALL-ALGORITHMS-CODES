#include<iostream>
#include<stdio.h>
#include<queue>
#include<stdlib.h>
#include<time.h>
using namespace std;
class Graph
{
	public:
		struct pair
		{
			int weight;
			int vertex;
		};
		struct mycompare
		{
			bool operator()(struct pair p,struct pair d)
			{
				return p.weight>d.weight;
			}
		};
		int A[100][100];
		int dist[100];
		int visited[100];
		int parent[100];
		int vertexcount;
		int src;
		int edgecount;
		priority_queue<struct pair,vector<struct pair>,mycompare>q1;
		FILE *fptr;
		Graph(int n,int s);
		int degree(int u);
		void addedge(int u,int v,int cost);
		int *neighbours(int u);
		int vertexcardinality();
		int edgecardinality();
		void dijkstra(int g,clock_t begin);
		int nodes_expanded();
		void addedge();
		int length=0;
		void printpath(int source,int goal);
};
Graph::Graph(int n,int s)
{
	fptr = fopen("Analysis_of_UCS.txt", "a");
	int i,j;
	src=s;
	vertexcount=n;
	edgecount=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			A[i][j]=0;
			dist[i]=99999;
			visited[i]=0;
			parent[i]=-1;
		}
	}
	struct pair p;
	p.weight=0;
	p.vertex=src;
	dist[src]=0;
	parent[src]=-1;
	q1.push(p);
	addedge();
}
void Graph::addedge()
{
	FILE *file = fopen ("Graph_Data_Edges.txt", "r" );
	if ( file != NULL )
	{
		char line [ 128 ]; 
		while(fgets(line, sizeof line, file ) != NULL ) 
		{
			char u[128],v[128],edges_cost[128];
			int flag=0,k=0,l=0,flag1=0,z=0;
			for(int i=0;i<10;i++)
			{
				if(line[i]==' ')
					flag=1;
				if(line[i]=='e')
					flag1=1;
				if(flag1==1 && line[i]!='e')
				{
					edges_cost[z]=line[i];
					z=z+1;
				}
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
			A[atoi(u)][atoi(v)]=atoi(edges_cost);
			A[atoi(v)][atoi(u)]=atoi(edges_cost);

		}
		fclose (file);
	}
}

int Graph::vertexcardinality()
{
	return vertexcount;
}
int Graph::edgecardinality()
{
	return edgecount;
}
int Graph::degree(int u)
{
	int count=0;
	for(int i=1;i<=vertexcount;i++)
	{
		if(A[u][i]>0)
			count++;
	}
	return count;
}
int* Graph::neighbours(int u)
{
	int *set;
	int count=0;
	set=new int[degree(u)+1];
	for(int i=1;i<=vertexcount;i++)
	{
		if(A[u][i]>0)
			set[++count]=i;
	}
	return set;
}
void Graph::dijkstra(int goal,clock_t begin)
{
	fprintf(fptr,"%d ",src);
	fprintf(fptr,"%d ",goal);
	int* set;
	int nodes=0;
	while(q1.size()>=1)
	{
		struct pair x;
		x=q1.top();
		if(x.vertex==goal)
		{
			printpath(src,goal);
			clock_t end=clock();
		  	double ts=(double)(end-begin)/CLOCKS_PER_SEC;
		  	fprintf(fptr,"%lf ",ts);
		  	printf("\n");
		  	printf("%lf seconds to execute\n",ts);
			nodes=nodes_expanded();
			fprintf(fptr,"%d ",nodes);
			fprintf(fptr,"%d ",length-1);
			fprintf(fptr,"\n");
			exit(0);
		}
		else
		{
			q1.pop();
			visited[x.vertex]=1;
			set=neighbours(x.vertex);
			for(int i=1;i<=degree(x.vertex);i++)
			{
				int k=set[i];
				if(visited[k]==0)
				{
					if(dist[x.vertex]+A[x.vertex][k]<dist[k])
					{
						dist[k]=dist[x.vertex]+A[x.vertex][k];
						struct pair t;
						t.weight=dist[k];
						t.vertex=k;
						parent[t.vertex]=x.vertex;
						q1.push(t);
					}
				}
			}
		}
	}
}
int Graph::nodes_expanded()
{
	int nodes=0;
	for(int i=1;i<=89;i++)
	{
		if(visited[i]==1)
		{
			nodes=nodes+1;
		}
	}
	return nodes;
}
void Graph::printpath(int s,int t)
{
	int k;
	if(t==s)
	{
		length++;
		printf("path: %d",t);
		return;
	}
	else
	{
		length++;
		k=parent[t];
		printpath(s,k);
		printf("%c",' ');
		printf("%d",t);
	}
}

int main()
{
	clock_t begin=clock();
	int u,v,g,cost,s,n=89;
	printf("source\n");
	cin>>s;
	printf("goal\n");
	cin>>g;
	Graph G(n,s);	
	G.dijkstra(g,begin);
	/*for(int i=1;i<=n;i++)
	{
		printf("%d %d\n",i,G.dist[i]);
	}*/
	cout<<endl;
	return 0;
}



