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
//	grid(PIXELHEIGHT);
	moveto(200,10);
	setcolor(10);
	outtext("Convex Hull by Graham Scan Algorithm");

	//.....store the points in the set_of_points class
	set_of_points spt;
	spt.input_points(DRAWNOT);

	//........define polygon
	polygon poly;
	poly.convex_hull_graham_scan_algorithm(spt.pt,spt.np);
	poly.print_polygon();

	v.waitforrightclick();
}