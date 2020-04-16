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

	setpixelheight(1);
//	grid(PIXELHEIGHT);
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
			check_if_exit_is_clicked(p);
			pt[i]=p;
		}
		else break;
	}
	int np=i;   //.....np is number of points entered

	//.......find leftmost point of set
	point leftmost=pt[0];
	int a=0;
	for(i=0;i<np;i++){
		if(pt[i].x<leftmost.x){
			leftmost=pt[i];
			a=i;
		}
	}
	pt[np]=pt[a];
	vputpixel(leftmost,10);
v.waitforrightclick();
	//swap(pt[a],pt[0]);

	//....sort the points by polar angle subtended on lowest point
	polygon poly;
	for(int m=0;m<np;m++){
		swap(pt[a],pt[m]);
		poly.add_point(pt[m]);
		a=m+1;
		for(int i=m+2;i<np;i++){
			int c=pt[i].classify_point_position_wrt_line_segment(pt[m],pt[a]);
			if(c==LEFT||c==BEYOND)
				a=i;
		}
		if(a==np)break;
	}

	for(i=0;i<poly.np-1;i++){
		vline(poly.pt[i],poly.pt[i+1]);//(i+1)%poly.np]);
	}
	v.waitforrightclick();
}