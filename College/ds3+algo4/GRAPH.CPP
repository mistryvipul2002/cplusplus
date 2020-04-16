//................perfectly correct program...........
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>
#include<process.h>
#include<math.h>
#define INF 3.4e38
#define PI 3.14
#define WT_DATA float
enum{FALSE=0,TRUE=1,UNDIRECTED=2,DIRECTED=3,CIRCLE_RADIUS=20,MAX=50};
void error(){
	cout<<"\nError................\n";
}
//==============STACK   TEMPLATE   CLASS======================
template <class STACKTYPE>class stack{
	STACKTYPE p[MAX];
	int top;
public:
	stack(){top=-1;}
	copy(stack stk){
		top=stk.top;
		for(int i=0;i<=top;i++)p[i]=stk.p[i];
	}
	void push(STACKTYPE t){
		if(top+1==MAX){cout<<"Can't push....overflow";exit(0);}
		p[++top]=t;
	}
	STACKTYPE pop(){
		if(top==-1){cout<<"Can't pop....";exit(0);}
		return(p[top--]);
	}
	int empty(){
		if(top==-1)return(TRUE);
		return(FALSE);
	}
	STACKTYPE stacktop(){
		return p[top];
	}
	void print(){
		for(int i=top;i>=0;i--)
			cout<<p[i]<<"<-";
	}
};
//===========MAIN GRAPH CLASS====================
class graph{
public:
	//=========member variables==========
	WT_DATA cost[MAX][MAX];
	int connected[MAX][MAX];
	int graph_type;//..DIRECTED or UNDIRECTED
	int tot_nodes,tot_edges;

	//==============CONSTRUCTOR AND DESTRUCTOR SECTION
	graph(){
		for(int i=0;i<MAX;i++)
			for(int j=0;j<MAX;j++){
				if(i==j){
					connected[i][j]=1;
					cost[i][j]=0;
				}
				else{
					connected[i][j]=FALSE;
					cost[i][j]=INF;
				}
			}
		tot_nodes=0;tot_edges=0;
	}
	~graph(){}
	//===================MEMBER FUNCTIONS==========
	void add_node(int a,int b,WT_DATA weight){
		//......add a node only if its weight is lower then earlier
		cost[a][b]=weight;
		connected[a][b]=TRUE;
		if(graph_type ==UNDIRECTED){
			cost[b][a]=weight;
			connected[b][a]=TRUE;
		}
		tot_edges++;
	}
	void shortest_path(int v,stack<int> *stk,WT_DATA* dist){
		//....dist[j],1<=j<=tot_nodes is set to the length of
		//....the shortest path from vertex v to vertex j in a diagraph
		//....with "tot_nodes" vertices. dist[v] is set to 0.0.
		//....graph is represented by its cost adjacency matrix cost[][]
		//....WT_DATA is data type of cost of an edge

		//..........this works for both DIRECTED AND UNDIRECTED GRAPHS
		int S[MAX];
		for(int i=0;i<tot_nodes;i++){
			dist[i]=cost[v][i];
			S[i]=FALSE;
			if(connected[v][i]==TRUE)stk[i].push(i);
		}
		dist[v]=0;
		S[v]=TRUE;
		for(int num=1;num<tot_nodes;num++){
			//....determine (tot_nodes-1) paths from v
			//.....find u from vertices not in S and whose dist[u] is minimum
			WT_DATA min=INF;
			int u=0;
			for(i=0;i<tot_nodes;i++){
				if(S[i]==FALSE){
					if(dist[i]<min){
						min=dist[i];
						u=i;
					}
				}
			}
			S[u]=TRUE;   //....put u in S
			for(int w=0;w<tot_nodes;w++)
				if( (S[w]==FALSE) && (dist[w]>dist[u]+cost[u][w]) ){
					dist[w] = dist[u]+cost[u][w];
					stk[w].copy(stk[u]);
					stk[w].push(w);
				}
		}
	}
	//================PRINTING THE GRAPH=============
	void print_edge(int i,int j){
		float x1,y1,x2,y2;
		x1=320+200*cos(i*2*PI/tot_nodes);
		y1=240+200*sin(i*2*PI/tot_nodes);
		x2=320+200*cos(j*2*PI/tot_nodes);
		y2=240+200*sin(j*2*PI/tot_nodes);
		setcolor(RED);
		setlinestyle(SOLID_LINE,0,1);
		float length=sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
		line(x1+(CIRCLE_RADIUS/length)*(x2-x1),y1+(CIRCLE_RADIUS/length)*(y2-y1),
			x1+(1-CIRCLE_RADIUS/length)*(x2-x1),y1+(1-CIRCLE_RADIUS/length)*(y2-y1));
		setcolor(15);
		moveto(x1+(CIRCLE_RADIUS/length)*(x2-x1)+0.8*(1-2*(CIRCLE_RADIUS/length))*(x2-x1),
			  y1+(CIRCLE_RADIUS/length)*(y2-y1)+0.8*(1-2*(CIRCLE_RADIUS/length))*(y2-y1));
		char str[10];
		sprintf(str,"%.2f",cost[i][j]);
		outtext(str);

		setcolor(10);
		int small_radius=3;
		circle(x1+(1-(CIRCLE_RADIUS+small_radius)/length)*(x2-x1),y1+(1-(CIRCLE_RADIUS+small_radius)/length)*(y2-y1),small_radius);
		setfillstyle(1,10);
		floodfill(x1+(1-(CIRCLE_RADIUS+small_radius)/length)*(x2-x1),y1+(1-(CIRCLE_RADIUS+small_radius)/length)*(y2-y1),10);
	}
	void print_vertex(int i){
		char str[]="0";
		setcolor(15);
		moveto(320+200*cos(i*2*PI/tot_nodes),240+200*sin(i*2*PI/tot_nodes));
		str[0]='0'+i+1;
		outtext(str);
		circle(320+200*cos(i*2*PI/tot_nodes),240+200*sin(i*2*PI/tot_nodes),CIRCLE_RADIUS);
	}
	void print(){
		int gdriver = DETECT, gmode, errorcode;
		initgraph(&gdriver, &gmode, "\\tc\\bgi");
		for(int i=0;i<tot_nodes;i++){
			for(int j=0;j<tot_nodes;j++){
				if(connected[i][j]==FALSE||i==j)continue;
				print_edge(i,j);
			}
			print_vertex(i);
		}
		getch();closegraph();
	}
	//==============MEMBER FUNCTIONS FOR "UNDIRECTED" GRAPHS ONLY==========
	void depth_first_search(){
		//......only for undirected graph
		int *visited=new int[MAX];
		for(int i=0;i<MAX;i++)visited[i]=FALSE;
		for(i=0;i<tot_nodes;i++){
			if(visited[i]==TRUE)continue;
			DFS(i,visited);
		}
	}
	void DFS(int v,int *visited){
		//......used in depth_first_search() function
		visited[v]=TRUE;
		for(int i=0;i<tot_nodes;i++){
			if(connected[v][i]==FALSE||visited[i]==TRUE)continue;
			cout<<"("<<v+1<<","<<i+1<<","<<cost[v][i]<<") ";
			DFS(i,visited);
		}
	}
	WT_DATA prim(int **t){
		//.........t[tot_nodes][2] stores the minimum cost spanning tree
		int nearj[MAX],k,l;
		int cou=0;WT_DATA mincost;
		for(int i=0;i<tot_nodes;i++)
			for(int j=0;j<tot_nodes;j++){
				if(i==j||connected[i][j]==FALSE)continue;
				if(cou++==0)mincost=cost[i][j];
				if(cost[i][j]<mincost){
					mincost=cost[i][j];
					k=i;l=j;
				}
			}
		//....now (k,l) is edge of minimum cost in graph
		//..."mincost" is the cost of (k,l)
		t[0][0]=k;t[0][1]=l;	//....put the edge in edge list t

		for(i=0;i<tot_nodes;i++)	//....initialise nearj
			if(cost[i][l]<cost[i][k])nearj[i]=l;
			else nearj[i]=k;
		nearj[k]=nearj[l]=-1;
		for(i=1;i<tot_nodes-1;i++){	//....find (n-2)
								//...additional edges for t
			//....j is an index such that nearj[j]!=-1 and
			//....cost[j][nearj[j]] is minimum
			WT_DATA min;int cou=0,j=0;
			for(int c=0;c<tot_nodes;c++){
				if(nearj[c]==-1)continue;
				if(cou++==0){min=cost[c][nearj[c]];j=c;}
				if(cost[c][nearj[c]]<min){
					min=cost[c][nearj[c]];
					j=c;
				}
			}
			//........we have got index j
			t[i][0]=j;t[i][1]=nearj[j];
			mincost+=cost[j][nearj[j]];
			nearj[j]=-1;
			for(int k=0;k<tot_nodes;k++){
				if((nearj[k]!=-1) && (cost[k][nearj[k]]>cost[k][j]))
					nearj[k]=j;
			}
		}
		return(mincost);
	}
};
//=================MAIN FUNCTION===============
void main(){
	clrscr();
	cout.precision(2);
	cout<<"\n\n\t\tThis program is made by :- VIPUL MISTRY\n";
	cout<<"\n\tPress any key to continue...........";
	getch();
	//============PROGRAM STARTS
	clrscr();
	graph g;
	cout<<"Enter the type of graph (directed or undirected (d/u)?.....";
	char ch;cin>>ch;
	g.graph_type=(ch=='d'||ch=='D'?DIRECTED:UNDIRECTED);
	cout<<"Enter the number of nodes....";
	cin>>g.tot_nodes;
/*	g.tot_nodes=7;

	g.add_node(0,5,10);g.add_node(0,1,28);g.add_node(1,2,16);
	g.add_node(1,6,14);g.add_node(2,3,12);g.add_node(6,3,18);
	g.add_node(6,4,24);g.add_node(4,3,22);g.add_node(5,4,25);


/*	g.add_node(1,2,20);g.add_node(2,1,2);g.add_node(1,3,15);g.add_node(3,6,10);
	g.add_node(3,4,4);g.add_node(6,4,4);g.add_node(2,6,30);g.add_node(6,5,10);
	g.add_node(5,4,15);g.add_node(2,5,10);*/
/*	g.add_node(1,2,50);g.add_node(1,4,10);g.add_node(4,1,20);g.add_node(1,3,45);
	g.add_node(2,4,15);g.add_node(2,3,10);g.add_node(4,5,15);g.add_node(5,2,20);
	g.add_node(6,5,3);g.add_node(5,3,35);g.add_node(3,5,30);*/

	//.........Now enter links or edges
	cout<<"\nEnter a b c<enter> where a is tail,b is head and c is weight\n";
	cout<<"The nodes are numbered from 1 to "<<g.tot_nodes<<"\n";
	cout<<"Enter 0 0 0<enter> to end the list......\n";
	int x,y; WT_DATA w;
	while(1){
		cin>>x>>y>>w;
		if(x==0&&y==0&&w==0)break;
		if(x<1||x>g.tot_nodes||y<1||y>g.tot_nodes||x==y)error();
		g.add_node(x-1,y-1,w);
	}

	//============MENU SHOW=============
begin:	clrscr();
	cout<<"\n\n\t\t\tGraph Operations\n\n";
	cout<<"\t\t1) Graph Traversal\n";
	cout<<"\t\t2) Shortest Path\n";
	cout<<"\t\t3) Display Matrix\n";
	cout<<"\t\t4) Options for Undirected Graph\n";
/*	cout<<"\t\t6) Transpose of a Matrix\n";
	cout<<"\t\t7) Adjoint of Matrix\n";
	cout<<"\t\t8) Inverse of Matrix\n";
	cout<<"\t\t9) Rank of Matrix\n";
	cout<<"\t\tj) Find nth power of matrix\n";*/
	cout<<"\t\t5) Exit\n\n";
	cout<<"\t\t\t Enter your choice.........";
	cin>>ch;
	clrscr();
	switch(ch){
		case '1':	cout<<"\t\t\tGraph traversal: -\n\n";
				if(g.graph_type==UNDIRECTED){
					cout<<"\t\t1) Simple Traversal\n";
					cout<<"\t\t2) DFS Traversal\n";
					cout<<"\t\t\tEnter your choice....";
					char ch;cin>>ch;
					if(ch=='2'){
						cout<<"\n\n";
						g.depth_first_search();
						getch();goto begin;
					}
				}
				for(int i=0;i<g.tot_nodes;i++)
					for(int j=0;j<g.tot_nodes;j++){
						if(g.connected[i][j]==FALSE||i==j)continue;
						cout<<"("<<i+1<<","<<j+1<<","<<g.cost[i][j]<<") ";
					}
				getch();goto begin;
		case '2':	cout<<"\t\tShortest path : -\n\n";
				cout<<"Enter the source node.......";
				int src;cin>>src;src--;
				//.....src gives the source node, stk gives the shortest path,
				//.....dist gives the shortest distance
				stack<int>* stk = new stack<int>[MAX];
				WT_DATA *dist = new WT_DATA[MAX];
				g.shortest_path(src,stk,dist);
				for(i=0;i<g.tot_nodes;i++){
					cout<<"\ndistance from "<<src+1<<" to "<<i+1<<" is ....";
					if(dist[i]>=3.3e38)cout<<"INF";
					else cout<<dist[i];
					cout<<"\nThe path :- ";
					if(stk[i].empty()){cout<<"NO Path....";continue;}
					while(!stk[i].empty())
						cout<<stk[i].pop()+1<<"<-";
					cout<<src+1;
				}
				delete(stk);
				delete(dist);
				getch();goto begin;
		case '3': g.print();goto begin;
		case '4': if(g.graph_type==DIRECTED){
					cout<<"These options are for Undirected Graph only....";
					getch();goto begin;
				}
				cout<<"\t\t\tUndirected Graph Options: -\n\n";
				cout<<"\t\t1) Minimum Cost Spanning Tree\n";
				cout<<"\n\t\t\tEnter your choice....";
				char ch;cin>>ch;
				if(ch=='1'){
					cout<<"\n\n";
					//.....t[tot_nodes][2] stores the minimum cost spanning tree
					int **t=new int*[g.tot_nodes];
					for(i=0;i<g.tot_nodes;i++){
						t[i]=new int[2];
					}
					WT_DATA min_cost= g.prim(t);
					clrscr();
					graph g_span;
					g_span.tot_nodes=g.tot_nodes;
					cout<<"The minimum cost of spanning tree is......"<<min_cost<<"\n";
					for(i=0;i<g.tot_nodes-1;i++){
						cout<<"\n ("<<t[i][0]+1<<","<<t[i][1]+1<<")";
						g_span.add_node(t[i][0],t[i][1],g.cost[t[i][0]][t[i][1]]);
						g_span.add_node(t[i][1],t[i][0],g.cost[t[i][0]][t[i][1]]);
					}
					getch();
					g_span.print();
				}
				goto begin;
		case '5': break;
	}
}