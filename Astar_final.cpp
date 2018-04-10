#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<queue>
#include<time.h>

using namespace std;
struct node
{
	int vertex_number=0,f=0,g=0;

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
	int G[1000][1000],source,goal,vertexcount,set[1000],parent[1000];
	float heuristics[1000];
	priority_queue<struct node,vector<struct node>,myCompare_f>openq;
	queue <struct node> closedq;
	int checkopen(int v);
	int checkclosed(int v);
	void init(int n);
	int length=0;
	int* neighbours(int v);
	int degree(int v);
	int astar(int s,int g, FILE* f);
	void update(int child,int vertex,int score);
        void addedge();
	void printpath(int s,int t);

};
void Astar::init(int n)
{
	vertexcount=n;
	addedge();
}
void Astar::addedge()
{
	//FILE *file = fopen ("Graph_data.txt", "r" );
	FILE *file = fopen ("Graph_Data_Edges.txt", "r" );
        FILE *file1= fopen("heuristics_MM.txt 60","r");
	FILE *file3= fopen("out_astar.txt","w");
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
			fprintf(file3,"%d %d %d\n",atoi(u),atoi(v),G[atoi(u)][atoi(v)]);
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
			heuristics[i]=atof(line1);
			//printf("Heu:%f\n",heuristics[i]);
                        i++;
		}
		fclose (file1);
       }
}
int* Astar::neighbours(int v)
{
	int k=1;
	for(int i=1;i<=vertexcount;i++)
	{
		if(G[v][i]>0)
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
		if(G[v][i]>0)
			d++;
	}
	return d;
}
int Astar::checkclosed(int v)
{
	int flag=0;
	queue <struct node> copyclosedq;
	copyclosedq=closedq;
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
int Astar::checkopen(int v)
{
	int flag=0;
	priority_queue<struct node,vector<struct node>,myCompare_f>copyopenq;
	node temp;
	copyopenq=openq;
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
void Astar::update(int child,int vertex,int score)
{
	priority_queue<struct node,vector<struct node>,myCompare_f>copyopenq;
	while(openq.size()>0)
	{
		node x=openq.top();
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
		openq.pop();
	}
	openq=copyopenq;

}
int Astar::astar(int s,int g,FILE *f)
{
	source=s;
	goal=g;
	node temp;
	temp.vertex_number=s;
	temp.g=0;
	temp.f=temp.g+heuristics[s];
	parent[temp.vertex_number]=-1;
	openq.push(temp);
	while(openq.size()>0)
	{
		node fmin=openq.top();
		if(fmin.vertex_number==goal)
		{
			printf("u:%d\n",fmin.g);
			fprintf(f,"%d ",closedq.size());
			//fprintf(f,"\n");
			printpath(source,goal);
		}
		openq.pop();
		closedq.push(fmin);
		int* nei=neighbours(fmin.vertex_number);
		for(int i=1;i<=degree(fmin.vertex_number);i++)
		{
			int belong_closed=checkclosed(nei[i]);
			if(belong_closed==1)
			{

				continue;
			}		
			int notbelong_open=checkopen(nei[i]);
			if(notbelong_open==0)
			{
				temp.vertex_number=nei[i];
				temp.g=fmin.g+G[fmin.vertex_number][nei[i]];
				temp.f=temp.g+heuristics[nei[i]];
				parent[nei[i]]=fmin.vertex_number;
				openq.push(temp);
			}
			else
			{
				int tempg=fmin.g+G[fmin.vertex_number][nei[i]];
				if(tempg>=notbelong_open)
					continue;
				else
				{
					update(nei[i],fmin.vertex_number,tempg);

				}
			}
		}
	}
}
void Astar::printpath(int s,int t)
{
	int k;
	if(t==s)
	{
		length++;
		printf("%d",t);
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
	Astar a;
	int s,n=89,g;
	FILE *fptr;
   	fptr = fopen("analysis_astar.txt", "a");
		
	printf("Enter the source node\n");
	scanf("%d",&s);
	fprintf(fptr,"%d ",s);

	printf("Enter the destination node\n");
	scanf("%d",&g);
	fprintf(fptr,"%d ",g);

	a.init(n);
	a.astar(s,g,fptr);
	clock_t end=clock();
        double ts=(double)(end-begin)/CLOCKS_PER_SEC;
	fprintf(fptr,"%lf ",ts);
	//fprintf(fptr,"%d ",a.closedq.size());
	fprintf(fptr,"%d ",a.length-1);
	fprintf(fptr,"\n");

        printf("\n");
        printf("%lf seconds to execute\n",ts);
        return 0;
}
