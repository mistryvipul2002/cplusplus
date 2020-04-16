#include<vmousenw.h>    //......this includes point.h further
#define MAX 100
void main()
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  // an error occurred
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); // terminate with an error code
	}

	//.......initialise mouse
	int maxx=getmaxx(),maxy=getmaxy();
	if(v.initmouse()==0)
	{
		closegraph();
		restorecrtmode();
		printf("\nMouse driver not loaded");
		exit(1);
	}
	v.restrictmouseptr(0,0,maxx,maxy);

	grid(50);
	moveto(200,10);
	setcolor(10);
	outtext("Convex Hull by Graham Scan Algorithm");
	moveto(600,460);
	outtext("Exit");
	//.....store the points using mouse
	point p;
	point pt[MAX];

	//.....enter the points
	setcolor(15);
	for(register int i=0;i<MAX;i++){
		if(v.waitforaclick(p)==LEFT){
			vputpixel(p,15);
			check(p);
			pt[i]=p;
		}
		else break;
	}
	int np=i;   //.....np is number of points entered

	//.......find lowest point of set
	point lowest;
	for(i=0;i<np;i++){
		if(pt[i].y<lowest.y){
			lowest=pt[i];
		}
	}

	//....sort the points by polar angle subtended on lowest point
	point less;int pos;
	for(i=0;i<np;i++){
		pos=i;less=pt[i];
		for(int j=i+1;j<np;j++){
			if(anglesubtendedby(pt[j],lowest)<anglesubtendedby(less,lowest)){
				less=pt[j];pos=j;
			}
		}
		swap(pt[pos],pt[i]);
	}

	//.....apply graham scan
	stack <point>list;
	point p1=pt[0],p2=pt[1];
	list.push(pt[0]);
	list.push(pt[1]);
	for(i=2;i<np;i++){
		if(turn(p1,p2,pt[i])==RIGHT){
			while(turn(p1,p2,pt[i])!=LEFT){
				list.pop();
				p2=list.pop();
				p1=list.pop();
				list.push(p1);
				list.push(p2);
			}
			list.push(pt[i]);
			p1=p2;
			p2=pt[i];
		}
		else{
			p1=p2;
			p2=pt[i];
			list.push(p2);
		}
	}

	//.......we get hull in 'list' stack
	point pttemp=lowest,pttmp;
	while(!list.empty()){
		pttmp=list.pop();
		vline(pttemp,pttmp);
		pttemp=pttmp;
	}

	v.waitforaclick(pttmp);
	check(pttmp);
}