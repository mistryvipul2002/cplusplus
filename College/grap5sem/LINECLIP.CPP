//......Code for Liang-Barsky parametric line clipping algorithm
#include<vmousenw.h>    //......this includes point.h further
#define MAX 100         //......define the maximum number of lines
#define TRUE 1
#define FALSE 0
vmouse v;
int xmin,xmax,ymin,ymax;
int clipt(int den,int num,float &te,float &tl){
	float t;
	if(den>0){
		t=((float)num)/den;
		if(t>tl)return FALSE;
		else te=(t>te?t:te);
	}
	else if(den<0){
			t=((float)num)/den;
			if(t<te) return FALSE;
			else tl=(tl<t?tl:t);
		}
		else if(num>0)return FALSE;
	return TRUE;
}
void clip2D(float &x0,float &y0,float &x1,float &y1,int &visible){
	float dx=x1-x0,dy=y1-y0;
	visible=FALSE;
	if(dx==0&&dy==0&&x0>=xmin&&x0<=xmax&&y0>=ymin&&y0<=ymax)
		visible=TRUE;
	else{
		float te=0.,tl=1.;
		if(clipt(dx,xmin-x0,te,tl))
		  if(clipt(-dx,x0-xmax,te,tl))
		    if(clipt(dy,ymin-y0,te,tl))
			 if(clipt(-dy,y0-ymax,te,tl)){
				visible=TRUE;
				if(tl<1){
					x1=x0+tl*dx;
					y1=y0+tl*dy;
				}
				if(te>0){
					x0+=te*dx;
					y0+=te*dy;
				}
			 }
	}
}
void main()
{	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
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

	//.....store the points using mouse
	int x,y,button;
	point pt[MAX][2];

	for(int i=0;i<MAX;i++){
		v.getpt(pt[i][0]);
		v.getpt(pt[i][1]);
		vline(pt[i][0],pt[i][1]);

		v.showmouseptr();
		v.getmousepos(&button,&x,&y);
		//....wait for a click
		while((button&1)!=1&&(button&2)!=2)v.getmousepos(&button,&x,&y);
		if((button & 2)==2)break;   //....if it is right click
	}
	int np=i+1;   //.....np is number of lines entered

	//......draw rectangle
	v.getpt(xmin,ymin);
	v.getpt(xmax,ymax);

	if(xmin>xmax){int temp=xmax;xmax=xmin;xmin=temp;}
	if(ymin>ymax){int temp=ymax;ymax=ymin;ymin=temp;}

/*	moveto(xmin,ymin);outtext("minimum");
	moveto(xmax,ymax);outtext("maximum");*/

/*	//.......code for testing one fixed line and fixed rectangle
	int np=1;
	pt[0][0].x=100;
	pt[0][0].y=300;
	pt[0][1].x=500;
	pt[0][1].y=200;
	vline(pt[0][0],pt[0][1]);
	xmin=200;ymin=200;
	xmax=400;ymax=400;
	// ......code for test*/

	rectangle(xmin,ymin,xmax,ymax);
	v.waitforrightclick();

	//.....algorithm starts here
	clearviewport();
	moveto(200,10);
	outtext("Line Clipping Algorithm");
	setcolor(10);
	rectangle(xmin,ymin,xmax,ymax);
	setcolor(15);

	//......for each line
	float x0,y0,x1,y1;    //......P0 is (x0,y0) and P1 is (x1,y1)
	int visible=TRUE;
	for(i=0;i<np;i++){
		x0=pt[i][0].x;
		y0=pt[i][0].y;
		x1=pt[i][1].x;
		y1=pt[i][1].y;
		clip2D(x0,y0,x1,y1,visible);
		if(visible==TRUE)line(x0,y0,x1,y1);
	}
	v.waitforrightclick();
	closegraph();
}