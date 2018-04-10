#include <bits/stdc++.h>
#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<time.h>
#include<stdlib.h>
using namespace std;

class Graph
{
	public:
	int vertexcount,set[1000],G[1000][1000];
	int visited_f[100];
	int visited_b[100];
	int parent_f[100];
	int parent_b[100];
	void init(int n);
	FILE *fptr;
   	void BFS(queue <int> q,int visited[100],int parent[100]);
	void biSearch(int src,int dest,clock_t t);
	void printPath(int s, int t, int intersectNode);
	void addedge();
	int isIntersecting();
	int degree(int s);
	int* neighbours(int s);
	int nodes_expanded();
};
void Graph::init(int n)
{
	fptr = fopen("analysis_bibfs.txt", "a");
	int i,j,count=0,p,k;
	vertexcount=n;
	for(i=1;i<=vertexcount;i++)
	{
		parent_f[i]=0;k=1;
		parent_b[i]=0;
		for(j=1;j<=vertexcount;j++)
		{
			G[i][j]=0;
		}
	}
	for(i=1;i<=vertexcount;i++)
	{
		visited_f[i]=0;
		visited_b[i]=0;		
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
		fclose ( file );
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
int Graph::isIntersecting()
{
	int insnode=-1;
	for(int i=1;i<=vertexcount;i++)
	{
		if(visited_f[i]==1 && visited_b[i]==1)
		{
			return i;
		}
	}
	return -1;
}

void Graph::biSearch(int src,int dest,clock_t begin)
{
	fprintf(fptr,"%d ",src);
	fprintf(fptr,"%d ",dest);
	queue <int> qf, qb;
	int insnode = -1;
	//Forward
	qf.push(src);
	visited_f[src] = 1;
	parent_f[src]=-1;

	//Backward
	qb.push(dest);
	visited_b[dest] = 1;
	parent_b[dest] = -1;
	while (!qf.empty() && !qb.empty())
	{
		BFS(qf,parent_f,visited_f);
		BFS(qb,parent_b,visited_b);
		insnode = isIntersecting();
		if(insnode != -1)
		{
			printf("Path found between %d and %d\n",src,dest);
			printf("Intersection at: %d\n",insnode);
			printPath( src, dest, insnode);
			clock_t end=clock();
			double ts=(double)(end-begin)/CLOCKS_PER_SEC;
			fprintf(fptr,"%lf ",ts);
			int e=nodes_expanded();
			fprintf(fptr,"%d ",e);
			fprintf(fptr,"\n");
			printf("\n");
			printf("%lf seconds to execute\n",ts);
			exit(0);
		}
	}
}

void Graph::BFS(queue <int> q1,int parent[100],int visited[100])
{
	int i,j,p,t,count=0,l,k;
	int *set1;
	t=q1.front();
	set1=neighbours(t);
	q1.pop();
	for(l=1;l<=degree(t);l++)
	{	
		if(visited[set[l]]!=1)
		{
			q1.push(set[l]);
			visited[set[l]]=1;
			parent[set[l]]=t;			
		}
	}
}

int Graph::nodes_expanded()
{
int expanded=0;
for(int i=1;i<=89;i++)
{
	if(visited_f[i]==1 || visited_b[i]==1)
	{
		expanded=expanded+1;
	}
}
	return expanded;
}

void Graph::printPath(int s, int t, int intersectNode)
{
	vector<int> path;
	path.push_back(intersectNode);
	int i = intersectNode;
	while (i != s)
	{
		path.push_back(parent_f[i]);
		i = parent_f[i];
	}
	reverse(path.begin(), path.end());
	i = intersectNode;
	while(i != t)
	{
		path.push_back(parent_b[i]);
		i = parent_b[i];
	}
	
	vector<int>::iterator it;
	cout<<"*****Path*****\n";
	for(it = path.begin();it != path.end();it++)
		cout<<*it<<" ";
	
	fprintf(fptr,"%d ",path.size()-1);
	cout<<"\n";
};

int main()
{
	clock_t begin=clock();
	Graph G;
	int n=89,k,s,i,g;

	printf("Enter the source node\n");
	scanf("%d",&s);

	printf("Enter the destination node\n");
	scanf("%d",&g);

	G.init(n);
	G.biSearch(s,g,begin);
	return 0;
}

