#include <vmouse.h>
#define MAXSIZE 100
double fact(int n)
{ 	if(n==0)return 1;
	double sum=1;
	for(int i=1;i<=n;i++)
	sum=sum*i;
	return(sum);
}
double comb(int n,int r)
{	return(fact(n)/(fact(n-r)*fact(r)));
}
float power(float b,int e)
{  float mul=1.0;
   for(int i=0;i<e;i++)
	mul=mul*b;
   return(mul);
}
int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "\\tc\\bgi");

   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
	 printf("Graphics error: %s\n", grapherrormsg(errorcode));
	 printf("Press any key to halt:");
	 getch();
	 exit(1); /* terminate with an error code */
   }

   int maxx=getmaxx();
   int maxy=getmaxy();

   //................our program starts...........
   printf("Use left mouse click to assign points..........\n");
   printf("Use right click to change screen...........\n");

   //.......initialise mouse
   vmouse v;int button,x,y;
   if(v.initmouse()==0)
   {
		closegraph();
		restorecrtmode();
		printf("\nMouse driver not loaded");
		exit(1);
   }
   v.restrictmouseptr(0,0,maxx,maxy);
   v.waitforrightclick();
   clearviewport();

   //.......initialise space for storing points
   int **pts=new int*[MAXSIZE];
   for(int i=0;i<MAXSIZE;i++){
	pts[i]=new int[2];
   }

   //.....store the points using mouse
   int np=0;  //......np means total number of points
   setcolor(10);
   v.showmouseptr();
   while(1){
	v.getmousepos(&button,&x,&y);
	if((button & 1)==1)
	{
		v.hidemouseptr();
		while((button & 1)==1)	v.getmousepos(&button,&x,&y);
		if(np>MAXSIZE)break;
		pts[np][0]=x;
		pts[np][1]=y;
		putpixel(pts[np][0],pts[np][1],15);
		np++;
		char str[5];
		sprintf(str," %d",np);
		moveto(x,y);
		outtext(str);
		v.showmouseptr();
	}
	if((button & 2)==2)  //..........when right click done break out of loop
	{
		while((button & 2)==2)	v.getmousepos(&button,&x,&y);
		if(np==0)continue;
		else break;
	}
   }
   v.hidemouseptr();
   //.......initialise space for storing points for use in
   //.......Bezier(nth order) and B-Spline curve
   int **pts1=new int*[MAXSIZE];
   for(i=0;i<MAXSIZE;i++){
	pts1[i]=new int[2];
   }
   //.....copy the points in pts1 as they will be changed in following curve
   for(i=0;i<np;i++){
	pts1[i][0]=pts[i][0];
	pts1[i][1]=pts[i][1];
   }
   int np1=np;   //.....np1 is no of points entered by user

   //=========================================================================
   //.......Bezier with cubic polynomial curve
   //.....add required number of points to make "np" of form (3n+1)
   int n=np%3;
   if(n==0){
	pts[np][0]=pts[np-1][0];
	pts[np][1]=pts[np-1][1];
	np++;
   }
   if(n==2||np==1){
	pts[np][0]=pts[np-1][0];
	pts[np][1]=pts[np-1][1];
	pts[np+1][0]=pts[np-1][0];
	pts[np+1][1]=pts[np-1][1];
	if(np==1){
		pts[np+2][0]=pts[np-1][0];
		pts[np+2][1]=pts[np-1][1];
		np+=3;
	}
	else np+=2;
   }
   //......modify points to maintain positional, tangential continuity
   for(i=1;i<np-1;i++){
	if(i%3==0){
		pts[i][0]=(pts[i-1][0]+pts[i+1][0])/2.;
		pts[i][1]=(pts[i-1][1]+pts[i+1][1])/2.;
	}
   }

   //.....now draw the curve
   setcolor(15);
   float xcur,ycur,sumx,sumy;
   for(i=0;i<(np-1);i+=3){
	sumx=sumy=0.0;
	xcur=pts[i][0];ycur=pts[i][1];
	for(float t=0.0;t<=1.0;t+=0.0009){
		sumx += 	power(1-t,3)*pts[i][0]+
				3*power(1-t,2)*t*pts[i+1][0]+
				3*(1-t)*power(t,2)*pts[i+2][0]+
				power(t,3)*pts[i+3][0];

		sumy += 	power(1-t,3)*pts[i][1]+
				3*power(1-t,2)*t*pts[i+1][1]+
				3*(1-t)*power(t,2)*pts[i+2][1]+
				power(t,3)*pts[i+3][1];
		line(xcur,ycur,sumx,sumy);
		xcur=sumx;ycur=sumy;
		sumx=sumy=0.0;
	}
   }
   moveto(200,20);
   setcolor(10);
   outtext("Bezier Curve - The Cubic Polynomial Curve");

   //========================================================
   //........Bezier curve nth order
   v.waitforrightclick();
   setcolor(15);
   clearviewport();
   xcur=pts1[0][0];ycur=pts1[0][1];
   sumx=sumy=0.0;
   for(float t=0.0;t<=1.0;t+=0.0009){
	for(int i=0;i<np1;i++){
		sumx += comb(np1-1,i)*power(1-t,np1-1-i)*power(t,i)*pts1[i][0];
		sumy += comb(np1-1,i)*power(1-t,np1-1-i)*power(t,i)*pts1[i][1];
	}
	line(xcur,ycur,sumx,sumy);
	xcur=sumx;ycur=sumy;
	sumx=sumy=0.0;
   }
   line(xcur,ycur,pts1[np1-1][0],pts1[np1-1][1]);
   setcolor(10);
   for(int j=0;j<np1;j++){
	moveto(pts1[j][0],pts1[j][1]);
	putpixel(pts1[j][0],pts1[j][1],15);
	char str[5];
	sprintf(str," %d",j+1);
	outtext(str);
   }
   moveto(200,20);
   outtext("Bezier Curve - Nth Order Polynomial");

   //========================================================
   //........B-Spline Curve
   v.waitforrightclick();

   //.....minimum 4 points are required
   for(i=0;i<(np1<4?4-np1:-1);i++){
	pts1[np1+i][0]=pts1[np1-1][0];
	pts1[np1+i][1]=pts1[np1-1][1];
	np1=4;
   }

   clearviewport();
   //.......print points with numbers
   for(j=0;j<np1;j++){
	setcolor(10);
	moveto(pts1[j][0],pts1[j][1]);
	putpixel(pts1[j][0],pts1[j][1],15);
	char str[5];
	sprintf(str," %d",j+1);
	outtext(str);
   }

   //....draw the curve
   setcolor(15);
   float mat[4][4]={   	{-1./6,	.5,		-.5,		1./6},
					{.5,		-1,		0.5,		0},
					{-.5,	0,		.5,		0},
					{1./6,	2./3,	1./6,	0}
			    };
   sumx=sumy=0.0;
   for(int c=0;c<np1-3;c++){
	for(float t=0.0;t<=1.0;t+=0.0009){
		for(int i=0;i<4;i++){
			float temp=mat[0][i]*t*t*t+mat[1][i]*t*t
					 +mat[2][i]*t+mat[3][i];
			sumx += temp*pts1[c+i][0];
			sumy += temp*pts1[c+i][1];
		}
		if(t==0.)putpixel(sumx,sumy,0);
		else line(xcur,ycur,sumx,sumy);
		xcur=sumx;ycur=sumy;
		sumx=sumy=0.0;
	}
   }

   setcolor(10);
   moveto(200,20);
   outtext("B-Spline Curve");

   //=============================================================
   v.waitforrightclick();
   closegraph();
   return 0;
}