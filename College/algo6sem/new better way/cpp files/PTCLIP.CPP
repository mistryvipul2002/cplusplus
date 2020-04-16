#include<vmousenw.h>    //......this includes point.h further
int pointinrectangle(point pt[MAX],int np,int x,int y,point p1,point p2){
	//......for each point
	int cou = 0;
	for(int i=0;i<np;i++){
		if(pt[i].x!=p1.x&&pt[i].x!=p2.x&&pt[i].y!=p1.y&&pt[i].y!=p2.y)
			if(pt[i].x<x && pt[i].y<y)cou++;
	}
	return(cou);
}
void main()
{
	vmouse v;
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

	setpixelheight(10);
	moveto(200,10);
	setcolor(10);
	outtext("Range Search Count Algorithm");
	moveto(600,460);
	outtext("Exit");

	point pt[MAX],p;

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

	point pmin,pmax;
	pmin.x=pmin.y=0;
	pmax.x=pmax.y=0;
	while(1){
		setcolor(0);
		vrectangle(pmin,pmax);

		//.........draw points
		for(int i=0;i<np;i++)
			vputpixel(pt[i],15);

		//......get endpoints of rectangle
		v.getpt(pmin);vputpixel(pmin,15);check_if_exit_is_clicked(pmin);
		v.getpt(pmax);check_if_exit_is_clicked(pmax);

		if(pmin.x>pmax.x)swap(pmax.x,pmin.x);
		if(pmin.y>pmax.y)swap(pmax.y,pmin.y);

		//.......draw rectangle
		setcolor(4);
		vrectangle(pmin,pmax);

		//.........draw points
		for(i=0;i<np;i++)
			vputpixel(pt[i],15);

		//.....algorithm starts here
		gotoxy(12,1);
		cout<<"   ";
		gotoxy(1,1);
		cout<<"Points :- "<<pointinrectangle(pt,np,pmax.x,pmax.y,pmax,pmin)-
						pointinrectangle(pt,np,pmax.x,pmin.y,pmax,pmin)-
						pointinrectangle(pt,np,pmin.x,pmax.y,pmax,pmin)+
						pointinrectangle(pt,np,pmin.x,pmin.y,pmax,pmin);
		v.waitforrightclick();
	}
}