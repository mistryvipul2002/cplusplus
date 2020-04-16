#include<vmousenw.h>
void main(){
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
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
	outtext("Convex Polygon Inclusion Algorithm");
	moveto(600,460);
	outtext("Exit");

	//.....store the points using mouse
	polygon poly;
	//.....enter the lines
	poly.input();
	//......find cg of polygon
	point q= poly.cg();
	setcolor(1);
	for(int i=0;i<poly.np;i++)vline(poly.pt[i],q);

	//......check if it is convex polygon
	if(!poly.convex()){
		cout<<"Not a convex polygon......";
		v.waitforrightclick();
		exit(0);
	}
	//......put points in anti clockwise fashion
	poly.orient(ANTICLOCKWISE);

	//...........apply algorithm
	point p,earlierpt;
	int k=0;
	gotoxy(1,1);
	cout<<"Point inside :- ";
	while(1){
		v.getpt(p);
		if(k!=0)vputpixel(earlierpt,0);//.....remove earlier point
		vputpixel(p,15);	//....mark the point
		check(p);      	//...check if user wants to exit
		gotoxy(17,1);cout<<"    ";
		if(poly.pointinside(p)){
			gotoxy(17,1);cout<<"YES";
		}
		else{
			gotoxy(17,1);cout<<"NO ";
		}
		earlierpt=p;
		k=1;
	}
}