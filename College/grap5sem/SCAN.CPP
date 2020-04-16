#define COLOR GREEN
#include<math.h>
#include<vmousenw.h>
int round(float i){
	int j=(int)i;
	if(i>(float)(j+.5))return(j+1);
	return(j);
}
void circlepts(int x1,int y1,int x,int y){
	putpixel(x1+x,y1+y,COLOR);
	putpixel(x1+y,y1+x,COLOR);
	putpixel(x1+y,y1-x,COLOR);
	putpixel(x1+x,y1-y,COLOR);
	putpixel(x1-x,y1-y,COLOR);
	putpixel(x1-y,y1-x,COLOR);
	putpixel(x1-y,y1+x,COLOR);
	putpixel(x1-x,y1+y,COLOR);
}
void mycircle(point p1,int radius){
	int x1,y1;p1.get(x1,y1);
	putpixel(x1,y1,COLOR);
	moveto(x1,y1);outtext(" Origin");
	moveto(200,10);
	outtext("Scan Circle Algorithm");

	int x=0,y=radius;
	float d=5./4.-radius;
	circlepts(x1,y1,x,y);

	while(y>x){
		if(d<0)	d+=2.*x+3.;
		else {	d+=2.*(x-y)+5.;
				y--;
		}
		x++;
		circlepts(x1,y1,x,y);
	}
}
void myline_middle_pt(point p1,point p2){
	int x1,y1,x2,y2;
	p1.get(x1,y1);
	p2.get(x2,y2);
	vmoveto(p1);outtext(" (x1,y1)");
	vmoveto(p2);outtext(" (x2,y2)");
	moveto(200,10);
	outtext("Scan Line Algorithm-middle point");

	int x,y,dx,dy,incE,incNE;
	float d;
	float m=(float)(y2-y1)/(x2-x1);
	if(m<=1&&m>=-1){
		if(x1>x2){
			int temp=x1;x1=x2;x2=temp;
			temp=y1;y1=y2;y2=temp;
		}
		if(m<0){y1=-y1;y2=-y2;}
		dx=x2-x1;dy=y2-y1;
		d=dy-0.5*dx;
		incE=dy;incNE=dy-dx;
		x=x1;y=y1;
		if(m>=0)putpixel(x,y,COLOR);
		else putpixel(x,-y,COLOR);
		while(x<=x2){
			if(d>=0){	d=d+incNE;
					x++;y++;
			}
			else{     d=d+incE;
					x++;
			}
			if(m>=0)putpixel(x,y,COLOR);
			else putpixel(x,-y,COLOR);
		}
	}
	else{
		if(y1>y2){
			int temp=x1;x1=x2;x2=temp;
			temp=y1;y1=y2;y2=temp;
		}
		m=1/m;
		if(m<0){x1=-x1;x2=-x2;}
		dx=x2-x1;dy=y2-y1;
		d=dx-0.5*dy;
		incE=dx;incNE=dx-dy;
		x=x1;y=y1;
		if(m>=0)putpixel(x,y,COLOR);
		else putpixel(-x,y,COLOR);
		while(y<=y2){
			if(d>=0){	d=d+incNE;
					x++;y++;
			}
			else{     d=d+incE;
					y++;
			}
			if(m>=0)putpixel(x,y,COLOR);
			else putpixel(-x,y,COLOR);
		}
	}
}
void myline_DDA(point p1,point p2){
	int x1,y1,x2,y2;
	p1.get(x1,y1);
	p2.get(x2,y2);
	vmoveto(p1);outtext(" (x1,y1)");
	vmoveto(p2);outtext(" (x2,y2)");
	moveto(200,10);
	outtext("Scan Line Algorithm-DDA");
	putpixel(x1,y1,COLOR);putpixel(x2,y2,COLOR);

	float m=(float)(y2-y1)/(x2-x1);
	if(m<=1&&m>=-1){
		if(x1>x2){
			int temp=x1;x1=x2;x2=temp;
			temp=y1;y1=y2;y2=temp;
		}
		float prevy=y1;
		for(int i=x1+1;i<=x2;i++){
			putpixel(i,round(prevy+m),COLOR);
			prevy=prevy+m;
		}
	}
	else{
		if(y1>y2){
			int temp=x1;x1=x2;x2=temp;
			temp=y1;y1=y2;y2=temp;
		}
		m=1/m;
		float prevx=x1;
		for(int i=y1+1;i<=y2;i++){
			putpixel(round(prevx+m),i,COLOR);
			prevx=prevx+m;
		}
	}
}
void main()
{	int gdriver =DETECT, gmode, errorcode;
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
	vmouse v;int maxx=getmaxx(),maxy=getmaxy();
	if(v.initmouse()==0)
	{
		closegraph();
		restorecrtmode();
		printf("\nMouse driver not loaded");
		exit(1);
	}
	v.restrictmouseptr(0,0,maxx,maxy);

	point p1,p2;

	//.....store the points using mouse
	v.getpt(p1);
	v.getpt(p2);

	//.........scan line DDA
	myline_DDA(p1,p2);
	v.waitforrightclick();

	//..........scan line middle pt
	clearviewport();
	myline_middle_pt(p1,p2);
	v.waitforrightclick();

	//.................scan circle algo
	clearviewport();
	int x1,y1,x2,y2;p1.get(x1,y1);p2.get(x2,y2);
	mycircle(p1,sqrt(float(x2-x1)*(x2-x1)+float(y2-y1)*(y2-y1)));
	v.waitforrightclick();
	closegraph();
}