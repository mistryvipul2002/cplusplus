#include<dos.h>
#include<iostream.h>
#include<bios.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<alloc.h>
//...........to make your own drawing
void makbem();
void select(int,int);
void main()
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }

   //......program starts now..........
   int key,x=5,y=30,col,spd; //....x,y denotes the current cordinates of the point
   //...........2nd page of progarm
   cout<<"\n\t\t\tP A I N T     B R U S H\n";
   cout<<"\t\t\t=======================\n\n";
   cout<<"A Program by-----------> VIPUL MISTRY\n\n";
   cout<<"Enter the starting cordinates?\n";
   cout<<"Enter x (1-624)? ";cin>>x;        //....start from cordinates as user likes
   cout<<"Enter y (1-438)? ";cin>>y;

   //...........set the color of drawing
   //.....array used to print current color
   char color[16][13]={"Black","Blue","Green","Cyan","Red","Magneta","Brown","Lightgrey",
		"Darkgrey","Lightblue","Lightgreen","Lghtcyan","Lightred",
		"Lightmagneta","Yellow","White"};
   cout<<"\n";
   cout<<"Black--0    Red-------4  Darkgray----8  Lightred-----12\n";
   cout<<"Blue---1    Magneta---5  Lightblue---9  LightMagneta-13\n";
   cout<<"Green--2    Brown-----6  LightGreen-10  Yellow-------14\n";
   cout<<"Cyan---3    LightGray-7  Lightcyan--11  White--------15\n";
   cout<<"\nEnter the code for color? ";
   cin>>col;
   cout<<"\nEnter speed of drawing(1-10)?  ";
   cin>>spd;spd--;
   clearviewport();   //...clear screen

   //.........3rd page (instruction page) of progarm
   gotoxy(1,1);
   cout<<"\n\n\t\t\tInstructions\n";
   cout<<"\t\t\t============";
   cout<<"\n\n\n\t1) Use cursor keys to draw";
   cout<<"\n\t2) Press u to put the pen up";
   cout<<"\n\t3) Press d to put the pen down";
   cout<<"\n\t4) Press space to see options menu";
   cout<<"\n\t5) Press enter to quit the program";
   cout<<"\n\nThis is a program to draw figures through keyboard.";
   cout<<"\n\nPress any key to continue.........";
   bioskey(0);
   clearviewport();
   //.........designing of working page of program
   setcolor(7);
   rectangle(1,26,634,474); //....outer rectangle---light gray
   rectangle(5,30,630,470); //....inner rectangle---light gray
   setcolor(15);         //.....fill inside inner rectangle----white
   setfillstyle(1,15);
   floodfill(6,31,7);
   setcolor(7);          //...fill outer portion----light gray
   setfillstyle(1,7);
   floodfill(4,29,7);

   //............now our work on page starts
   gotoxy(1,1);
   cout<<"Your cordinates are ";
   gotoxy(21,1);
   cout<<x<<","<<y;     //.....write initial cordinates
   x=x+5;y=y+30;

   int pen=0;                //......initialilly pen is down
   setcolor(col);
   gotoxy(42,1);
   cout<<"Pen=";
   if(pen==0)cout<<"down";
   else cout<<"up  ";
   gotoxy(32,1);
   cout<<"Speed="<<spd+1;
   gotoxy(52,1);
   cout<<"Color="<<color[col];

start:key=bioskey(0);      //.....get the key pressed by user
   int size;void *saucer;
   switch(key)        //...different cases for different keys
     {
       case 19712 :if((x+1+spd>629)||(y>469)||(x+1+spd<6)||(y<31))
			cout<<"\a";
		   else{
			if(pen==1)moveto(x+1+spd,y);
			else {
				 line(x,y,x+1+spd,y);       //if key pressed is right
			     }
			x=x+1+spd;
		       }
		   break;
       case 19200 :if((x-1-spd>629)||(y>469)||(x-1-spd<6)||(y<31))
			cout<<"\a";
		   else{
			if(pen==1)moveto(x-1-spd,y);
			else {
			       line(x,y,x-1-spd,y);    //if key pressed is left
			     }
			x=x-1-spd;
		       }
		   break;
       case 18432 :if((x>629)||(y-1-spd>469)||(x<6)||(y-1-spd<31))
			cout<<"\a";
		   else{
			if(pen==1)moveto(x,y-1-spd);
			else {
				 line(x,y,x,y-1-spd);//if key pressed is up
			     }
			y=y-1-spd;
		       }
		   break;
       case 20480 :if((x>629)||(y+1+spd>469)||(x<6)||(y+1+spd<31))
			cout<<"\a";
		   else{
			if(pen==1)moveto(x,y+1+spd);
			else {
			       line(x,y,x,y+1+spd);//if key pressed is down
			     }
			y=y+1+spd;
		       }
		   break;
       case 14624 ://.........save image as it is going to be used by menu
		   size=imagesize(200,100,520,370);   //....get size of image
		   saucer=malloc(size);          //....allocate the memory
		   getimage(200,100,520,370,saucer);  //.....store the image

		   //......open a options menu................
		   //......main rectangle for menu
		   setcolor(0);
		   rectangle(200,100,500,350); //....make a rectangle-black
		   //......making its shadow
		   setcolor(0);
		   setfillstyle(1,0);
		   bar(220,350,520,370); //....make a rectangle-black
		   bar(500,120,520,350); //....make a rectangle-black

	     begin:makbem();//.......make main menu
		   //....write text in it.............
		   moveto(290,120);
		   settextstyle(2,0,7);
		   outtext("Option Menu");
		   setlinestyle(0,0,3);  //.....thick line
		   line(290,155,418,155);  //....for underlining the text
		   setlinestyle(0,0,0);
		   settextstyle(2,0,5);
		   moveto(240,180);
		   outtext("1) Change colour");
		   moveto(240,200);
		   outtext("2) Change speed");
		   moveto(240,220);
		   outtext("3) Change cordinates");
		   moveto(240,240);
		   outtext("4) Fill color");
		   moveto(240,260);
		   outtext("5) Save/Load Picture");
		   moveto(240,280);
		   outtext("6) Exit");//...add option of drawing shapes circle
		   moveto(235,310);
		   outtext("Press your choice.....");

		   //........get choice of user in variable cho
		   int cho;
	    begin2:cho=bioskey(0);

		   switch(cho)
		   {
		    case 561:makbem();
			     moveto(220,200);       //1 pressed
			     outtext("Enter color? Press 2 digits");
			     moveto(220,220);
			     outtext("from 00 to 15");
			     int cho1,cho2;
			     fcloseall();
			     cho1=getch()-48;
			     cho2=getch()-48;
			     col = cho1*10+cho2;
			     goto begin;
		    case 818:makbem();
			     moveto(220,200);  //...if choice is 2
			     outtext("Enter the speed? Press 2 digits");
			     fcloseall();
			     spd=(getch()-48)*10+getch()-48-1;
			     goto begin;
		    case 1075:makbem();         //...if 3
			     moveto(220,180);
			     outtext("Enter x cordinate(0-624)?");
			     moveto(220,200);
			     outtext("Press 3 digits");
			     x=(getch()-48)*100+(getch()-48)*10+(getch()-48)+5;
			     moveto(220,240);
			     outtext("Enter y cordinate(0-438)?");
			     moveto(220,260);
			     outtext("Press 3 digits");
			     y=(getch()-48)*100+(getch()-48)*10+(getch()-48)+30;
			     goto begin;
		    case 1332:makbem();
			     moveto(220,180);
			     outtext("Choose fill color. Press two digits..");
			     int col1=(getch()-48)*10+getch()-48;
			     moveto(220,200);
			     outtext("Enter boundary color.Press 2 digits..");
			     int col2=(getch()-48)*10+getch()-48;
			     moveto(220,220);
			     outtext("This will fill space with fillcolor");
			     moveto(220,240);
			     outtext("Choose a point inside the space and");
			     moveto(220,260);
			     outtext("press enter to finally fill.");
			     moveto(220,280);
			     outtext("Press a key to start choose...");
			     bioskey(0);
			     putimage(200,100,saucer,COPY_PUT);  //.....put image again
			     free(saucer);
			     select(x,y);
			     setcolor(col1);
			     setfillstyle(1,col1);
			     extern x1,y1;
			     floodfill(x1,y1,col2);
			     setcolor(col);
			     goto start;
		    case 1589://..........when 5 pressed
			     makbem();
			     moveto(220,180);
			     outtext("1) Save by picture.pic");
			     moveto(220,200);
			     outtext("2) Load picture.pic");
			     moveto(220,220);
			     outtext("Enter your choice.........");
		       again:switch(bioskey(0))
			     {
			      case 561 ://..........save
					remove("picture.pic");
					FILE *fp;
					fp=fopen("Picture.pic","w");
					putimage(200,100,saucer,COPY_PUT);  //.....put image again
					free(saucer);
					for(int v=1;v<=438;v++)
					for(int u=1;u<=624;u++)
					  fprintf(fp,"%d ",getpixel(u+5,v+30));
					fclose(fp);
					setcolor(col);
					goto start;
			      case 818: //............load
					FILE *fp1;
					fp1=fopen("picture.pic","r");
					int colr;
					for(v=1;v<=438;v++)
					for(u=1;u<=624;u++)
					 {
					  fscanf(fp1,"%d",&colr);
					  putpixel(u+5,v+30,colr);
					 }
					fclose(fp1);
					x=1+5;y=1+30;
					setcolor(col);
					free(saucer);
					goto start;
			      default : goto again;
			     }
			     break;
		    case 1846:break;  //....when 6 pressed
		    default:goto begin2;
		   }
		   putimage(200,100,saucer,COPY_PUT);  //.....put image again
		   free(saucer);//....free the allocated memory
		   setcolor(col);          //...restore original color
		   setlinestyle(0,0,0);//..restore original attributes of line
		   break;
       case 5749  :pen=1;     //..penup
		   break;
       case 8292  :pen=0;     //..pendown
		   break;
       case 7181  :gotoxy(67,1);//if enter is pressed, end the program
		   cout<<"Exit(y/n)?";
		   char choi=getche();
		   if(choi=='Y'||choi=='y')goto end;
		   else { gotoxy(67,1);
			  cout<<"          ";
			  break;
			}
     }
   gotoxy(21,1);
   cout<<"       ";
   gotoxy(21,1);
   cout<<x-5<<","<<y-30;   //...write current cordinates
   gotoxy(32,1);
   cout<<"Speed="<<spd+1;
   gotoxy(42,1);
   cout<<"Pen=";
   if(pen==0)cout<<"down";
   else cout<<"up  ";
   gotoxy(52,1);
   cout<<"Color="<<color[col];
   goto start;     //...if any other key is pressed it will goto start
   end:;
   closegraph();
}
//.........make grey rectangle
void makbem()
{
 setcolor(7);
 setfillstyle(1,7);
 bar(201,101,499,349);
 setcolor(0);
}
int x1,y1;
void select(int x,int y)
{
int col=getpixel(x,y);
x1=x;y1=y;
beg: int ch=bioskey(0);
 putpixel(x1,y1,col);
 switch(ch)
 {
  case 19712://....to see the right screen
	     x1++;break;
  case 19200://....to see the left screen
	     x1--;break;
  case 18432://....to see the up screen
	     y1--;break;
  case 20480://....to see the down screen
	     y1++;break;
  case 7181://........enter is pressed
	    return;
  default: goto end1;
 }
end1:col=getpixel(x1,y1);
 putpixel(x1,y1,0);
 goto beg;
}