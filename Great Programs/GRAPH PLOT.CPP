#define PI 3.14
#define ERRORS 0
#include<bios.h>
#include<conio.h>
#include<process.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include<iostream.h>
#include<string.h>
float x,y1;
int gin(float y);
int matherr (struct exception *a)
{
  if (a->type == DOMAIN)
    if (!strcmp(a->name,"sqrt")) {
      a->retval = ERRORS;//sqrt(-1*(a->arg1));
    return 1;
    }
  return 0;
}

void main()
{
   clrscr();
   float mark,spd;
   cout<<"Want marks on axis at intervals of ?";
   cin>>mark;
   cout<<"Enter the speed of magnification(1-20)?";
   cin>>spd;
   clrscr();

   //.......activate graphics mode
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "\\tc\\bgi");

   //....draw x and y axes in red
   setcolor(4);
   line(320,1,320,470);
   line(1,240,639,240);

   //....all variable declarations are here as after that goto loop starts
   //....and noone can initialise variables inside 'goto'
   float j,scale=spd/10,xact,yact,xcur=0,ycur=0,xold,yold;
   int cou;
   float a,q,r;
a: //....wait for user to press a key
   switch(bioskey(0))
   {
    case 5993 ://....i used to magnify the graph
	       //....variable 'scale' checks the magnification of graph
	       clearviewport();scale+=spd/10;break; //....if 'i' was pressed
    case 8292 ://....d is used to demagnify the graph
	       clearviewport();scale-=spd/10;break; //..if 'd' key pressed
    //(xcur,ycur) are cordinates of centre of current screen
    //....in front of you w.r.t. the centre of original screen
    case 20273://....to see the lower left screen
	       clearviewport();xcur--;ycur--;break;//..if 1 key pressed
    case 20530://....to see the down screen
	       clearviewport();ycur--;break;    //..if 2 key pressed
    case 20787://....to see the lower right screen
	       clearviewport();xcur++;ycur--;break; //..if 3 key pressed
    case 19252://....to see the left screen
	       clearviewport();xcur--;break;    //..if 4 key pressed
    case 19766://....to see the right screen
	       clearviewport();xcur++;break;    //..if 6 key pressed
    case 18231://....to see the up and left screen
	       clearviewport();xcur--;ycur++;break; //..if 7 key pressed
    case 18488://....to see the up screen
	       clearviewport();ycur++;break;    //..if 8 key pressed
    case 18745://....to see the up and right screen
	       clearviewport();xcur++;ycur++;break; //..if 9 key pressed
    case 18176://....to go to main screen
	       clearviewport();xcur=0;ycur=0;break; //..if home key pressed
    case 7181 :goto b;    //....if enter is pressed exit the program
   }
   //....draw cordinate axes acccording to the current screen
   setcolor(4);
   if(xcur==0.)  line(320,1,320,470);
   if(ycur==0.)  line(1,240,639,240);

   //...reset the color to green since graph will be plotted in green only
   setcolor(10);

   //...if magnification(i.e. scale) is very less it will
   //...not be possible to show the graph
   if(scale<=0)
   { gotoxy(1,1);
     cout<<"cannot demagnify more...";
     //....restore the scale to 0 if further demagnification is attempted
     scale=0.;
     //....and goto beginning i.e. at label a
     goto a;
   }

   //...draw the marks on x and y axis at the spacing specified by user
   //...only when axis is shown (this part is not complete)

   //.....put cou equal to 0 as the loop is beginning
   cou=0;
   //......to use following in polar form use below line
 //  for(q=0;q<=2*3.14;q+=.01)
  for(xact=(-320.0+640.*xcur)/scale;
	   xact<=(320.+640.*xcur)/scale;
	   xact+=1/scale)
	{
/*	 r=q;//.......to write function in polar use these 3 lines
	 xact=r*cos(q);
	 yact=r*sin(q);*/
	  x=xact;
	  //..............write your function of x here;
	  yact= x*x;
	  //.....int cou increases by 1 each time loop is executed
	  //....when loop runs for first time assign values to xold and yold
	  if(cou==0){
		  xold=xact;
		  yold=yact;
		 }

       //....if points are too far don't print the line
       if(fabs(yact-yold)*scale<=240.&& sqrt(650*650-xact*xact)!=ERRORS)
       {
       line(320+(xact*scale-640*xcur),240-(yact*scale-480*ycur),
	       320+(xold*scale-640*xcur),240-(yold*scale-480*ycur));
       xold=xact;yold=yact;
       }

       //.....increase cou by 1 as here loop terminates
       cou++;
    }
   goto a;

  b:closegraph();
}
int gin(float y)
{
 if(y>=0.)return(int(y));
 else return(-1-int(fabs(y)));
}