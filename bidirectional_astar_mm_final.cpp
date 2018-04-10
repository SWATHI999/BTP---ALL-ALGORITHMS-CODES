#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<queue>
#include<time.h>
#include <bits/stdc++.h>

using namespace std;
struct node
{
	int vertex_number=0;
	float f=0,g=0;

};
struct myCompare_f
{
	bool operator()(struct node x,struct node y)
	{
		return x.f>y.f;
	}
};
class Astar
{
	public:
		int G[100][100],source,goal,vertexcount,set[100];
		float heuristics_f[100],heuristics_b[100];
		FILE *fptr;
		priority_queue<struct node,vector<struct node>,myCompare_f>openq;//Forward
		priority_queue<struct node,vector<struct node>,myCompare_f>openbackwardq;
		queue <struct node> closedq_forward;
		queue <struct node> closedq_backward;
		int checkopen(priority_queue<struct node,vector<struct node>,myCompare_f>opq,int v);
		int checkclosed(queue <struct node> q1,int v);

		int visited_f[100],visited_b[100],parent_f[100],parent_b[100];

		void init(int n);
		int* neighbours(int v);
		int isIntersecting();
		int degree(int v);
		int astar(int s,int g,priority_queue<struct node,vector<struct node>,myCompare_f>q1,int parent[100],int visited[100],queue<struct node> q2,float heuristics[100]);

		int Biastar(int s,int g,clock_t begin);

		void update(int parent[100],int child,int vertex,int score,priority_queue<struct node,vector<struct node>,myCompare_f>opq,float heuristics[100]);
		void addedge();
		void printpath(int s,int t,int k);
		int nodes_expanded();

};
void Astar::init(int n)
{
	vertexcount=n;
	addedge();
	fptr = fopen("Analysis_of_MM.txt", "a");
}
void Astar::addedge()
{
	//FILE *file = fopen ("Graph_data.txt", "r" );
	FILE *file = fopen ("Graph_Data_Edges.txt", "r" );
	FILE *file1= fopen("heuristics_MM.txt 60","r");
	FILE *file2= fopen("heuristics_MM.txt 57","r");
	//FILE *file3= fopen("out_astar.txt","w");
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
			G[atoi(u)][atoi(v)]=atoi(edges_cost);
			G[atoi(v)][atoi(u)]=atoi(edges_cost);
			//fprintf(file3,"%d %d %d\n",atoi(u),atoi(v),G[atoi(u)][atoi(v)]);
			//G[atoi(u)][atoi(v)]=1;
			//G[atoi(v)][atoi(u)]=1;

		}
		fclose (file);
	}
	if (file1!=NULL)
	{
		char line1 [ 128 ];
		int i=1; 
		while ( fgets ( line1, sizeof line1, file1 ) != NULL ) 
		{
			heuristics_f[i]=atof(line1);
			i++;
		}
		fclose (file1);
	}
	if (file2!=NULL)
	{
		char line1 [ 128 ];
		int i=1; 
		while ( fgets ( line1, sizeof line1, file2 ) != NULL ) 
		{
			heuristics_b[i]=atof(line1);
			i++;
		}
		fclose (file2);
	}

	for(int i=1;i<=vertexcount;i++)
	{
		visited_f[i]=0;
		visited_b[i]=0;
		parent_f[i]=0;
		parent_b[i]=0;
	}
}
int Astar::nodes_expanded()
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

int* Astar::neighbours(int v)
{
	int k=1;
	for(int i=1;i<=vertexcount;i++)
	{
		if(G[v][i]>0.0)
		{
			set[k]=i;
			k++;
		}
	}
	return set;
}
int Astar::degree(int v)
{
	int d=0;
	for(int i=1;i<=vertexcount;i++)
	{
		if(G[v][i]>0.0)
			d++;
	}
	return d;
}
int Astar::checkclosed(queue <struct node> q1,int v)
{
	int flag=0;
	queue <struct node> copyclosedq;
	copyclosedq=q1;
	while(copyclosedq.size()>0)
	{
		node temp;
		temp=copyclosedq.front();
		if(temp.vertex_number==v)
		{
			flag=1;
			break;
		}
		copyclosedq.pop();
	}
	if(flag==1)
		return 1;
	else
		return 0;
}
int Astar::checkopen(priority_queue<struct node,vector<struct node>,myCompare_f>opq,int v)
{
	int flag=0;
	priority_queue<struct node,vector<struct node>,myCompare_f>copyopenq;
	node temp;
	copyopenq=opq;
	while(copyopenq.size()>0)
	{

		temp=copyopenq.top();
		if(temp.vertex_number==v)
		{
			flag=1;
			break;
		}
		copyopenq.pop();
	}
	if(flag==1)
		return temp.g;
	else
		return 0;
}
void Astar::update(int parent[100],int child,int vertex,int score,priority_queue<struct node,vector<struct node>,myCompare_f>opq,float heuristics[100])
{
	priority_queue<struct node,vector<struct node>,myCompare_f>copyopenq;
	while(opq.size()>0)
	{
		node x=opq.top();
		if(x.vertex_number==child)
		{
			x.vertex_number=child;
			x.g=score;
			parent[x.vertex_number]=vertex;
			x.f=x.g+heuristics[x.vertex_number];
			copyopenq.push(x);
		}
		else
		{
			copyopenq.push(x);
		}
		opq.pop();
	}
	opq=copyopenq;

}
int Astar::Biastar(int src,int dest, clock_t begin)
{
	fprintf(fptr,"%d ",src);
	fprintf(fptr,"%d ",dest);	
	int insnode = -1;
	//Forward
	node temp;
	temp.vertex_number=src;
	temp.g=0;
	temp.f=temp.g+heuristics_f[src];
	openq.push(temp);
	visited_f[src] = 1;
	parent_f[src]=-1;

	//Backward
	temp.vertex_number=dest;
	temp.g=0;
	temp.f=temp.g+heuristics_b[dest];
	openbackwardq.push(temp);
	visited_b[dest] = 1;
	parent_b[dest] = -1;
	

	astar(src,dest,openq,parent_f,visited_f,closedq_forward,heuristics_f);
	astar(dest,src,openbackwardq,parent_b,visited_b,closedq_backward,heuristics_b);
	insnode = isIntersecting();
	//printf("Ins:%d\n",insnode);
	if(insnode != -1)
	{
		printf("Path found between %d and %d\n",src,dest);
		printf("Intersection at: %d\n",insnode);
		printpath( src, dest, insnode);
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
int Astar::astar(int s,int g,priority_queue<struct node,vector<struct node>,myCompare_f>q1,int parent[100],int visited[100],queue<struct node> q2,float heuristics[100])
{
	while (!q1.empty())
	{
		node fmin=q1.top();
		if(fmin.vertex_number==g)
		{
			return fmin.vertex_number;
		}
		node temp;		
		q1.pop();
		q2.push(fmin);
		visited[fmin.vertex_number]=1;
		int* nei=neighbours(fmin.vertex_number);
		for(int i=1;i<=degree(fmin.vertex_number);i++)
		{
			int belong_closed=checkclosed(q2,nei[i]);
			if(belong_closed==1)
			{
				continue;
			}		
			int notbelong_open=checkopen(q1,nei[i]);
			if(notbelong_open==0)
			{
				temp.vertex_number=nei[i];
				temp.g=fmin.g+G[fmin.vertex_number][nei[i]];
				temp.f=temp.g+heuristics[nei[i]];
				parent[nei[i]]=fmin.vertex_number;
				q1.push(temp);
			}
			else
			{
				int tempg=fmin.g+G[fmin.vertex_number][nei[i]];
				if(tempg>=notbelong_open)
					continue;
				else
				{
					update(parent,nei[i],fmin.vertex_number,tempg,q1,heuristics);

				}
			}
		}
	}
}
void Astar::printpath(int s,int t,int intersectNode)
{
	int k;
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
}
int Astar::isIntersecting()
{
	//printf("Intersect\n");
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
int main()
{
	clock_t begin=clock();
	Astar a;
	int s,n=89,g;

	printf("Enter the source node\n");
	scanf("%d",&s);

	printf("Enter the destination node\n");
	scanf("%d",&g);

	a.init(n);
	a.Biastar(s,g,begin);

	printf("\n");
	return 0;
}
