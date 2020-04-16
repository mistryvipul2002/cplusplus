//===========this program has slight problem somewhere==========
#include<dos.h>
#include<iostream.h>
#define INF 9999
#define MAX 100000
enum {UNDIRECTED=0,DIRECTED=1};
class stack
{		int *stk;
		int top;
	public:
		stack()	{top=-1;}
		void initialise(int size)
		{ stk=new int[size];	}
		void push(int element)
		{	stk[++top]=element;	}
		int pop()
		{	return(stk[top--]);	}
		void print();
		void stack_copy(stack s2);
};
void stack::print()
{	for(int i=0;i<=top;i++)
		cout<<stk[i]+1<<((i!=top)?"->":"\n");
}
void stack::stack_copy(stack s2)   //....copy s2 to current stack
{	for(int i=0;i<=s2.top;i++)
	   stk[i]=s2.stk[i];
	top=s2.top;
}
struct node
		{	int link;
			int weight;
			node *right;
		};
class graph
{		node *g;
		int v,e;//...v is total nodes,e is total edges
		int direct;
	public:
		int direct_undirect(){return(direct);}
		void make_graph();
		void error(){cout<<"\nAllocation error.........";}
		void print_nodes();
		void connect(int,int,int);
		node* search(int,node*);
		void dele_list(node*);
		int cost(int,int);
		void prim();
		void kruskal();
		void simple_union(int*,int,int);
		int find(int[],int);
		void shortest_path();
		~graph();
	 };
graph::~graph()
{	for(int i=0;i<v;i++) dele_list(&g[i]);
	delete g;
}
void graph::dele_list(node *list)
{//.....deletes list starting at list
//	if(list->right==NULL)delete list;
//	else dele_list(list->right);
}
void graph::make_graph()
{
	//..........enter total nodes
	cout<<"Enter directed or undirected graph (d/u)? ";
	char ch;cin>>ch;direct=(ch=='d'||ch=='D'?DIRECTED:UNDIRECTED);
	cout<<"Enter total number of nodes......";cin>>v;
	//........initialise
	g=new node[v];
	for(int i=0;i<v;i++) g[i].right=NULL;

	//.........now enter links or edges
	cout<<"\n\nEnter a b c<enter> where a is tail,b is head and c is weight\n";
	cout<<"The nodes are numbered from 1 to "<<v<<"\n";
	cout<<"Enter 0 0 0<enter> to end the list......\n";
	int first,second,weight;
	while(1)
	{ 	cin>>first>>second>>weight;
		if(first==0&&second==0&&weight==0)break;
		first--;second--;
		connect(first,second,weight);
	}
	//.....to find value of e i.e number of edges
	node *temp;
	e=0;
	for(i=0;i<v;i++)
	{  //....access children of temp
		temp=g[i].right;
		while(temp!=NULL)
		{	e++;
			temp=temp->right;
		}
	}
}
void graph::connect(int tail,int head,int weight)
{ 	if(tail<0||tail>=v||head<0||head>=v) //....if not valid nodes in list
	{ 	cout<<"Error in search for "<<tail+1<<" "<<head+1<<" "
			<<weight<<"....\n";
		return;
	}
	if(search(head,g[tail].right)!=NULL)
	{ 	cout<<"Link "<<tail+1<<","<<head+1<<" already exists....\n";
		return;
	}
	node *first=&g[tail];   //.....first is node in node list
	while(first->right!=NULL)first=first->right;
	first->right=new node;if(first->right==NULL)error();
	first=first->right;
	first->weight=weight;
	first->link=head;
	first->right=NULL;
}
node* graph::search(int c,node *start)
{	node *temp=start;
	while(temp!=NULL)
	{	if(temp->link==c) return(temp);
		temp=temp->right;
	}
	return(NULL);
}
void graph::print_nodes()
{ 	cout<<"\nEdges in the "<<(direct==UNDIRECTED?"undirected":"directed")<<" graph are.....(tail,head,cost)\n";
	node *temp;
	e=0;
	for(int i=0;i<v;i++)
	{  //....access children of temp
		temp=g[i].right;
		while(temp!=NULL)
		{	cout<<"("<<i+1<<","<<temp->link+1<<","<<temp->weight<<")\t";
			e++;
			temp=temp->right;
		}
	}
}
int graph::cost(int tail,int head)
{	node *t=search(head,g[tail].right);
	if(t==NULL)
	{ if(direct==UNDIRECTED)
	  {	if((t=search(tail,g[head].right))!=NULL)return(t->weight);    }
	  return(INF);
	}
	return(t->weight);
}
void graph::prim()
{   time t1,t2;
	gettime(&t1);
	long int count=0;

	//.....array t[v][2] which stores min spanning tree
	struct edge{int one,two;};
	edge *t=new edge[v-1];

	//.....create a array nearr[v]
	int *nearr=new int[v];

again:
	int min_wt=INF,k,l;
	//.....find edge <k,l> with minimum cost
	node *temp;
	for(int i=0;i<v;i++)
	{	temp=g[i].right;
		while(temp!=NULL)
		{	if(min_wt>(temp->weight))
			{	min_wt=temp->weight;
				k=i;
				l=temp->link;
			}
			temp=temp->right;
		}
	}
	int mincost=cost(k,l);

	//..first edge <k,l> included in t
	t[0].one=k;t[0].two=l;

	for(i=0;i<v;i++)
	   {  if(cost(i,l)<cost(i,k))nearr[i]=l;
		 else nearr[i]=k;
	   }
	nearr[k]=nearr[l]=-1;

	//......for remaining n-1 edges
	for(i=1;i<v-1;i++)
	{	int min=INF,pos=0;
		for(int j=0;j<v;j++)
			if(nearr[j]!=-1)
			{	if(cost(j,nearr[j])<min)
				{	min=cost(j,nearr[j]);pos=j;	}
			}
		j=pos;
		t[i].one=j;t[i].two=nearr[j];
		mincost=mincost+cost(j,nearr[j]);
		nearr[j]=-1;
		for(int k=0;k<v;k++)
		   if((nearr[k]!=-1)&&(cost(k,nearr[k])>cost(k,j)))
			nearr[k]=j;
	}
	if(count<MAX){count++;goto again;}
	gettime(&t2);

	//.....print the result
	cout<<"\n\nPrim's Algorithm=============>\n";
	cout<<"The minimum cost spanning tree is :- (tail,head,cost)\n";
	for(i=0;i<v-1;i++)
	  cout<<"("<<t[i].one+1<<","<<t[i].two+1<<","<<cost(t[i].one,t[i].two)<<")\t";
	cout<<"\nMinimum Cost of Tree is ="<<mincost;

	cout<<"\n\nThe time taken by prim algorithm when run "<<MAX<<" times = \n";
	int hund=t2.ti_sec*100+t2.ti_hund-t1.ti_sec*100-t1.ti_hund;
	cout<<int(hund/100)<<" seconds "<<int(hund%100)<<" milliseconds \n";
}
void graph::kruskal()
{
	time t1,t2;
	gettime(&t1);
	long int count=0;

	struct edges{int one,two;};
	edges *t=new edges[v-1];

	struct edge{int tail,head, cost,traverse;};
	edge *array=new edge[e];

	int *parent= new int[v];
	node*temp;

again2:
	int cou=0;
	for(int i=0;i<v;i++)
	{	temp=g[i].right;
		while(temp!=NULL)
		{    array[cou].tail=i;
			array[cou].head=temp->link;
			array[cou++].cost=temp->weight;
			temp=temp->right;
		}
	}
	for(i=0;i<e;i++)
		array[i].traverse=0;

	for(i=0;i<v;i++)parent[i]=-1;

	i=0;int mincost=0;
	while(i<v-1)
	{    int min=INF,pos;
		for(int j=0;j<e;j++)
		{    if(array[j].cost<min&&array[j].traverse==0)
			{	min=array[j].cost;
				pos=j;
			}
		}
		if(min==INF)break;
		array[pos].traverse=1;
		int a=array[pos].tail,b=array[pos].head;
		int p=find(parent,a),q=find(parent,b);
		if(p!=q)
		{	t[i].one=a;t[i].two=b;
			mincost=mincost+cost(a,b);
			simple_union(parent,p,q);
			i++;
		}
	}
	if(count<MAX){count++;goto again2;}
	gettime(&t2);
	cout<<"\n\nKruskal Algo================>\n";
	if(i!=v-1){cout<<"No spanning Tree";return;}
	cout<<"The minimum cost spanning tree is :- (tail,head,cost)\n";
	for(i=0;i<v-1;i++)
	  cout<<"("<<t[i].one+1<<","<<t[i].two+1<<","
		 <<cost(t[i].one,t[i].two)<<")\t";
	cout<<"\nMinimum Cost of Tree is ="<<mincost;

	cout<<"\n\nThe time taken by kruskal algorithm when run "<<MAX<<" times = \n";
	int hund=t2.ti_sec*100+t2.ti_hund-t1.ti_sec*100-t1.ti_hund;
	cout<<int(hund/100)<<" seconds "<<int(hund%100)<<" milliseconds \n";
}
int graph::find(int parent[],int i)
{ 	while(parent[i]>=0)i=parent[i];
	return(i);
}
void graph::simple_union(int *parent,int i,int j)
{	parent[i]=j;
}
void graph::shortest_path()
{   cout<<"\n\nDijikstra's Shortest Path Algorithm============>\n";
	cout<<"Enter the source node..........";
	int u;cin>>u;u--;
	int *S=new int[v],*dist=new int[v];

	stack *s=new stack[v];
	for(int y=0;y<v;y++)s[y].initialise(v);

	for(int i=0;i<v;i++)
	{	S[i]=0;dist[i]=cost(u,i);
		if(dist[i]!=INF&&dist[i]!=0)
		{	s[i].push(u);s[i].push(i);}
		else s[i].push(u);
	}
	S[u]=1;dist[u]=0;

	for(int num=2;num<=v-1;num++)
	{   int min=INF,pos=0;
		for(i=0;i<v;i++)
		{ 	if(S[i]==0)
			{	if(dist[i]<=min)
				{	min=dist[i];
					pos=i;
				}
			}
		}
		S[pos]=1;
		node *temp=g[pos].right;
		while(temp!=NULL)
		{   int next=temp->link;
			if(S[next]==0)
			{	if(dist[next]>dist[pos]+cost(pos,next))
				{	dist[next]=dist[pos]+cost(pos,next);
					s[next].stack_copy(s[pos]);
					s[next].push(next);
				}
			}
			temp=temp->right;
		}
	}
	cout<<"The shortest path from vertex "<<u+1<<" to \n";
	for(i=0;i<v;i++)
		{	cout<<"Vertex "<<i+1<<" = ";
			if(dist[i]==INF)cout<<"INF";
			else cout<<dist[i];
			cout<<"\n";
		}
	cout<<"\nThe shortest path from vertex "<<u+1<<" to \n\n";
	for(i=0;i<v;i++)
		{	cout<<"Vertex "<<i+1<<" is :- ";
			if(dist[i]==INF)cout<<"No Path.....\n\n";
			else { s[i].print();cout<<"\n";}
		}
	cout<<"\nWant to continue(y/n)? ";
	char ch;cin>>ch;
	if(ch=='y')shortest_path();
}
void main()
{	graph g;
	g.make_graph();
	g.print_nodes();
	if(g.direct_undirect()==UNDIRECTED)
	{	g.prim();
		g.kruskal();
	}
	g.shortest_path();
}