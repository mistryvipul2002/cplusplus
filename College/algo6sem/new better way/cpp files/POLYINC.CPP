#include<vmousenw.h>
void main(){
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
	outtext("Any Polygon Inclusion Algorithm");
	moveto(600,460);
	outtext("Exit");

	//.....store the points using mouse
	polygon poly;
	//.....enter the lines
	poly.input_points(DRAW);

	//...........apply algorithm
	point p,earlierpt;
	int k=0;
	gotoxy(1,1);
	cout<<"Point inside :- ";
	while(1){
		v.getpt(p);
		if(k!=0)vputpixel(earlierpt,0);//.....remove earlier point
		vputpixel(p,15);	//....mark the point
		check_if_exit_is_clicked(p);      	//...check if user wants to exit
		gotoxy(17,1);cout<<"    ";
		int value=poly.point_inside_ray_shoot_method_for_any_polygon(p);
		if(value==INSIDE){
			gotoxy(17,1);cout<<"YES     ";
		}
		else if(value==BOUNDARY){
			gotoxy(17,1);cout<<"BOUNDARY";
		}
		else {
			gotoxy(17,1);cout<<"NO      ";
		}
		earlierpt=p;
		k=1;
	}
}