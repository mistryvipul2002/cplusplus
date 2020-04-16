#include<vmousenw.h>    //......this includes point.h further
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
	moveto(200,10);
	setcolor(10);
	outtext("Convex Hull by Gift Wrapping Algorithm");

	//.....store the points using mouse
	set_of_points spt;
	spt.input_points(DRAWNOT);

	polygon poly;
	poly.convex_hull_gift_wrapping_algorithm(spt.pt,spt.np);

	//..............print the polygon
	poly.print_polygon();
	v.waitforrightclick();
}