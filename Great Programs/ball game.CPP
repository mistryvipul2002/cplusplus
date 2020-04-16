//..............................Ball Game by Vipul Mistry
#include<iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<math.h>
#include<dos.h>
void main()
{
   /* request auto detection  */
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
   settextstyle(1,0,9);
   moveto(80,100);
   setcolor(12);
   outtext("BALL GAME");
   moveto(370,400);
   settextstyle(1,0,3);
   setcolor(2);
   outtext("by VIPUL MISTRY");
   delay(3000);
   clearviewport();

   setcolor(12);
   moveto(200,30);
   outtext("Instruction Manual");
   line(195,55,415,55);
   setcolor(14);
   moveto(30,70);
   settextstyle(1,0,2);
   outtext("A ball will appear at the centre of a rectangle. You can");
   moveto(30,95);
   outtext("then start ball motion by pressing any key. To change");
   moveto(30,125);
   outtext("the direction of motion of ball put the numlock key");
   moveto(30,155);
   outtext("open and then use the numbers from 1 to 9 on numeric");
   moveto(30,180);
   outtext("keypad. Number 5 will cause the ball to stop. To end ");
   moveto(30,205);
   outtext("the game press the enter key.");
   moveto(30,300);
   outtext(" Hope you will enjoy the game made by one and only ");
   setcolor(12);
   settextstyle(1,0,4);
   moveto(200,350);
   outtext("Vipul Mistry");
   moveto(10,440);
   settextstyle(1,0,1);
   setcolor(14);
   outtext("Press any key to continue...........");
   getch();getch();
   clearviewport();

   int sidex,sidey,spd,rad,x1,y1,x2,y2,col;
   cout<<"\n\n\nEnter all data in positive integers and one by one....\n";
   cout<<"\nEnter the speed of ball(1-25)? ";
   cin>>spd;spd=25-spd;
   cout<<"\nEnter horizontal length of box(10-635)?\n";
   cin>>sidex;
   cout<<"\nEnter vertical height of box(10,475)?\n";
   cin>>sidey;
   x1=320-sidex/2;
   y1=240-sidey/2;
   x2=320+sidex/2;
   y2=240+sidey/2;
   cout<<"\nEnter the radius of ball between(1-";
   if(x2-x1<y2-y1)cout<<(x2-x1)/2;
   else cout<<(y2-y1)/2;
   cout<<") ?\n";
   cout<<"note that speed will decrease if radius is very large.....\n";
   cin>>rad;
   cout<<"\n";
   cout<<"Black--0    Red-------4  Darkgray----8  Lightred-----12\n";
   cout<<"Blue---1    Magneta---5  Lightblue---9  LightMagneta-13\n";
   cout<<"Green--2    Brown-----6  LightGreen-10  Yellow-------14\n";
   cout<<"Cyan---3    LightGray-7  Lightcyan--11  White--------15\n";
   cout<<"\nEnter the color of the ball? ";
   cin>>col;
   clearviewport();

//....verti and hori side of rectangle
setcolor(10);
rectangle(x1-1,y1-1,x1+sidex+1,y1+sidey+1);

//....calculating centre of rectangle
int cntrx=x1+sidex/2,cntry=y1+sidey/2;
setcolor(col);
circle(cntrx,cntry,rad);

//....fill the circle
setfillstyle(1,col);
floodfill(cntrx,cntry,col);

//...........to save the picture of ball in memory
void* buff;
int size=imagesize(cntrx-rad-1,cntry-rad-1,cntrx+rad+1,cntry+rad+1);
buff=malloc(size);
getimage(cntrx-rad-1,cntry-rad-1,cntrx+rad+1,cntry+rad+1,buff);

//.........(cntx,cnty) is centre of circle.....
//... disx and disy determines the direction of movement of ball...
//...(x,y) are cordinates of up-left corner of rectangle stored in memory
int cntx,cnty,disx=1,disy=0,x=cntrx-rad-1,y=cntry-rad-1;

//...we want initially the ball to remain at one position....
goto e;

d:while(kbhit())
  {
   e:switch(getch())
	{
	   case   54       :disx=1;disy=0;break;//....right
	   case   52       :disx=-1;disy=0;break;//.....left
	   case   56       :disy=-1;disx=0;break;//.....up
	   case   50       :disy=1;disx=0;break;//.....down
	   case   55       :disx=-1;disy=-1;break;//.....up left
	   case   53       :goto e;               //.....pause
	   case   49       :disx=-1;disy=1;break;//.....down left
	   case   57       :disx=1;disy=-1;break;//.....up right
	   case   51       :disx=1;disy=1;break;//.....down right
	   case   13       :free(buff);goto r;  //....if enter is pressed
			   //...free memory space and terminate the program
	   default         :goto c;
	}
  }
c:
//....change upper left cordinates of rectangle as per direction
x=x+disx;
y=y+disy;
//....to introduce speed factor.......
delay(spd);
putimage(x,y,buff,COPY_PUT);
//....calc. centre of circle.......
cntx=x+rad+1;cnty=y+rad+1;

//....checks whether ball collides diagonally with a corner..
if((x1+sidex-cntx==rad+1||cntx-x1==rad+1)&&(cnty-y1==rad+1||y1+sidey-cnty==rad+1))
	     {disx*=-1;disy*=-1;goto d;}
//....checks whether ball collodes with a wall....
else if((x1+sidex-cntx==rad+1)||(cntx-x1==rad+1)){disx*=-1; goto d;}
else if(cnty-y1==rad+1||y1+sidey-cnty==rad+1){disy*=-1;goto d;}
//....if ball donot collide anywhere....
goto d;
//......if enter was pressed during the execution*/
r:clearviewport();
setcolor(10);
moveto(200,200);
settextstyle(1,0,6);
outtext("Thank you");
delay(2000);
closegraph();
}