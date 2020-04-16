#define ER 0
#define MK 1
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<bios.h>
#include<dos.h>
#include<iostream.h>
int **arr=new int*[9];
int move(int,int);
int check();
void disp();
void help(int col);
void ga_end();
void circ(int x,int y,int flag);
void cir(int,int,int);
void sou(int);
int spc=43,rad=17,xin=320-4*spc,yin=240-4*spc;
int ch,idir1,jdir1,icur,jcur,icur1,jcur1,tot=0,move_last=0;
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
   //.......first page
   settextstyle(1,0,10);
   moveto(40,20);
   setcolor(10);
   outtext("Brainvita");
   delay(2000);
   clearviewport();

 //.......help page...........
 setcolor(12);
 settextstyle(4,0,4);
 moveto(190,10);
 outtext("About the game");
 setlinestyle(0,0,3);
/*
 is a game of single player.Start removing the marbles, one at a time.
 Marbles are removed by jumping over the adjacent marble in horizontal
 or vertical direction.Diagonal move is not allowed.The game is over when
 there is no chance for jumping over tha adjacent marble.
  */

 line(190,53,408,53);
 setlinestyle(0,0,0);
 moveto(50,60);
 settextstyle(1,0,0);
 setcolor(14);
 setusercharsize(55,80,6,8);
 outtext("Brainvita");
 setcolor(9);
 outtext("is a game of single player. Start removing the");
 moveto(3,90);
 outtext("marbles, one at a time. Marbles are removed by jumping ");
 moveto(3,120);
 outtext("over the adjacent marble in horizontal or vertical direction.");
 moveto(3,150);
 outtext("Diagonal move is not allowed.The game is over when there");
 moveto(3,180);
 outtext("is no chance for jumping over the adjacent marble.");
 //........paragraph changes
 moveto(60,220);
 outtext("The moves are of gray color and yellow circle around");
 moveto(3,250);
 outtext("a move show that it is the current move which can be");
 moveto(3,280);
 outtext("selected and moved. Besides you can use online help.");
 moveto(3,450);
 outtext("              Press any key to continue.......");
 moveto(3,368);
 setcolor(14);
 outtext("A Game by - Vipul Mistry and P.S.Gupta (B.Tech, ISM)");
 moveto(3,393);
 outtext("Prepared on - 15th Feb 2002");
 moveto(3,420);
 outtext("All Rights Reserved.");
 settextstyle(1,0,6);
 setcolor(12);
 for(int u=0;u<4;u++)
 {
 if(u==3)setcolor(4);
 moveto(155+u,305+u);
 outtext("Best of Luck");
 }
 rectangle(0,5,639,455);
 rectangle(1,6,638,454);
 bioskey(0);

  //.....dynamically allocate memory for 2 D array of 9 by 9
  for(int i=0;i<9;i++)
     arr[i]=new int[9];

  //.....putting unused spaces as 9, filled as 1 and empty as 0
  for(i=0;i<9;i++)
     for(int j=0;j<9;j++)
	{
	  if(i==0||i==8)arr[i][j]=9;
	  else  {
		 arr[i][0]=arr[i][8]=9;
		 if(i==1||i==2||i==6||i==7)
		    {
		     arr[i][3]=arr[i][4]=arr[i][5]=1;
		     arr[i][1]=arr[i][2]=arr[i][6]=arr[i][7]=9;
		    }
		 else { for(int k=1;k<8;k++)arr[i][k]=1;}
		}
	 }
   arr[4][4]=0;

  //.......now graphics design of game
  //....background of blue
  setfillstyle(1,11);
  bar(0,0,639,479);
  //.........big red circle
  setcolor(4);
  circle(320,240,180);
  setfillstyle(1,4);
  floodfill(320,240,4);
  //.......putting the places
  for(i=0;i<9;i++)
   for(j=0;j<9;j++)
     if(arr[i][j]==1)cir(i,j,8);//.....filled places of gray
     else if(arr[i][j]==0)cir(i,j,7);//......empty places of light gray
  disp();
  //.......help and quit
  settextstyle(1,0,1);
  setcolor(0);
  moveto(550,5);
  outtext("F1-Help");
  moveto(550,25);
  outtext("Esc-Quit");
  setcolor(4);
  rectangle(540,3,630,48);

  //.......now start playing.........
  circ(4,4,MK);//.......make circle at center(initial) place
  jcur=4,icur=4;  //...........for current position       //  jcur----->
a:switch(bioskey(0))                                      //  icur
  {                                                       //   |
   case 19712://....to go to right                             \/
	      if(arr[icur][jcur+1]==0||arr[icur][jcur+1]==1) //...if possible
		 {
		  circ(icur,jcur,ER);  //....erase earlier circle  outline
		  circ(icur,jcur+1,MK);//....make new circle outline
		  jcur++; //......change the current pos
		 }
	      goto a;
   case 19200://....to go to left
	      if(arr[icur][jcur-1]==0||arr[icur][jcur-1]==1)
		 {
		  circ(icur,jcur,ER);
		  circ(icur,jcur-1,MK);
		  jcur--;
		 }
	      goto a;
   case 18432://....to go to up
	      if(arr[icur-1][jcur]==0||arr[icur-1][jcur]==1)
		 {
		  circ(icur,jcur,ER);
		  circ(icur-1,jcur,MK);
		  icur--;
		 }
	      goto a;
   case 20480://....to go to down
	      if(arr[icur+1][jcur]==0||arr[icur+1][jcur]==1)
		 {
		  circ(icur,jcur,ER);
		  circ(icur+1,jcur,MK);
		  icur++;
		 }
	      goto a;
   case 15104://.......if F1 pressed
	      help(0);
	      sou(1);
	      bioskey(0);
	      help(11);
	      goto a;
   case 283://............if escape key pressed i.e. want to end the game
	    sou(0);
	    break;
   case 7181://.........to select a piece...........
	     if(arr[icur][jcur]==1) //....if there is sth in place then
	     {                      //....only you can select
	      setfillstyle(1,0);//.....fill black color in selected piece
	      floodfill(xin+spc*jcur,yin+spc*icur,14);
	      //......after a piece is selected scan for key pressed
	      b:switch(bioskey(0))
		{
		 case 3592://........unselect a piece if bkspc is pressed
			   setfillstyle(1,8);//...again fill gray color
			   floodfill(xin+spc*jcur,yin+spc*icur,14);
			   goto a;
		 case 19712://........move the piece to right by jumping
			    if(move(0,1)==1)//.....operation success i.e. piece is moved graphically after checking
				{
				  //......store directions of move as it would
				  //...be needed in ^u key
				  idir1=0;jdir1=1;
				  //.....and store its final position
				  icur1=icur;jcur1=jcur;
				  sou(1);  //....beep when moved
				  tot++;   //....increase total no. of moves by 1
				  disp();//....show new contents at bottom
				  if(check())  //.....check whether game ended or not
				    {   //.....i.e. check whether another piece can be moved
				     ga_end();//.....if game ended print 'game over' on screen
				     goto end; //....and end the program
				    }
				  goto a;
				}
			    else goto b; //.....if piece was unable to move
		 case 19200://........move the piece to left by jumping
			    if(move(0,-1)==1)//.....operation success
				{ idir1=0;jdir1=-1;icur1=icur;jcur1=jcur;sou(1);tot++;disp();if(check()){ga_end();goto end;}goto a;}
			    else goto b;
		 case 18432://........move the piece to up by jumping
			    if(move(-1,0)==1)//.....operation success
				{ idir1=-1;jdir1=0;icur1=icur;jcur1=jcur;sou(1);tot++;disp();if(check()){ga_end();goto end;}goto a;}
			    else goto b;
		 case 20480://........move the piece to down by jumping
			    if(move(1,0)==1)//.....operation success
				{ idir1=1;jdir1=0;icur1=icur;jcur1=jcur;sou(1);tot++;disp();if(check()){ga_end();goto end;}goto a;}
			    else goto b;
		 default:goto b;
		}
	     }
	     goto a;
   case 5653://......if ^u is pressed i.e. undo the move
	     //.....reverse colors of circles
	     cir(icur1,jcur1,7);
	     cir(icur1-idir1,jcur1-jdir1,8);
	     cir(icur1-2*idir1,jcur1-2*jdir1,8);
	     //......change matrice also
	     arr[icur1][jcur1]=0;arr[icur1-idir1][jcur1-jdir1]=1;arr[icur1-2*idir1][jcur1-2*jdir1]=1;
	     //.....erase pointer outer circle
	     circ(icur,jcur,ER);
	     //.....change current value of i,j to its old value
	     icur=icur1-2*idir1;jcur=jcur1-2*jdir1;
	     //....since current value are changed put pointer circle
	     circ(icur,jcur,MK);
	     tot--; //....decrease total no. of moves
	     disp(); //.....show new contents at bottom
	     goto a;
   default:goto a; //....if absurd key is pressed
  }
  //......after game is ended forcefully i.e when esc key is pressed
  setcolor(13);
  moveto(15,455);
  outtext("Want to exit(y/n)?");  //...ask the user
again:ch=bioskey(0);
  if(ch==12654||ch==12622)//.....if n is pressed means user wants to continue
  {
    setfillstyle(1,11);
    bar(15,455,220,480);
    goto a;
  }
  else if(!(ch==5497||ch==5465))//....if absurd key is pressed but not the y
       goto again;  //....again scan for the key
goto end1;  //......skip below line
end:bioskey(0);//....after game ends by itself it should wait to show the user that game has ended
end1:delete(arr); //....delete the pointer arr of matrice
  closegraph();
}
//.......to make pointer circle for showing current position
void circ(int i,int j,int flag)  //...flag means to erase or make
{
 if(flag==ER)setcolor(4);//......draw circle in color of backgrd i.e. erase it
 else setcolor(14);//.......yellow-actual color of pointer circle
 circle(xin+spc*j,yin+spc*i,rad+3);//........it is of radius rad+3 i.e. slightly bigger than move
}
//......to make move by a filled circle at i,j (w.r.t. matrice) of given color
void cir(int i,int j,int col)
{                                                  //             jdir=-1
 setcolor(14);//.....yellow(outer boundry of move) //             /\
 circle(xin+spc*j,yin+spc*i,rad);                  //    idir=-1<--|-->idir=1
 setfillstyle(1,col);   //..fill gray color        //              |
 floodfill(xin+spc*j,yin+spc*i,14);                //              |
}                                                  //             \/
int move(int idir,int jdir)    //-------------------------->     jdir=1
{
 if(arr[icur+idir][jcur+jdir]==1  //..if piece just after(icur,ycur)is filled
 &&arr[icur+2*idir][jcur+2*jdir]==0)  //...and just after that it is empty
    {
     //.......change graphically
     cir(icur,jcur,7);  //...current place and next place is putted empty i.e. light gray
     cir(icur+idir,jcur+jdir,7);
     cir(icur+2*idir,jcur+2*jdir,8);//...third position is filled with dark gray
     circ(icur,jcur,ER);//...erase current pointer circle
     circ(icur+2*idir,jcur+2*jdir,MK);//....set third position as current pointer
     //.....also refresh the positions in our matrice
     arr[icur][jcur]=arr[icur+idir][jcur+jdir]=0;arr[icur+2*idir][jcur+2*jdir]=1;
     icur+=2*idir;jcur+=2*jdir; //....increase current positions accordingly
     return(1);
    }
 return(0);
}
int check()
{
 for(int i=1;i<8;i++)
   for(int j=1;j<8;j++)
      {
       if(arr[i][j]==1)//....if there is a piece present at current position
       {
	if((arr[i][j+1]==1&&arr[i][j+2]==0)||(arr[i][j-1]==1&&arr[i][j-2]==0)
	||(arr[i-1][j]==1&&arr[i-2][j]==0)||(arr[i+1][j]==1&&arr[i+2][j]==0))
	//.......and a piece is there near it means game has not ended
	return(0);
       }
      }
 return(1);//....means no piece found and game is ended
}
void sou(int ch)
{
 if(ch==1){sound(500);delay(10);nosound();}//.....when a piece is moved
 else if(ch==0)  //.......if escape key is pressed
	 {sound(200);delay(60);sound(700);delay(60);sound(200);delay(60);nosound();}
      else if(ch==2){sound(700);delay(400);nosound();} //.....when game ends
}
void ga_end()
{
 //......when game ends
 sou(2);
 setcolor(12);
 settextstyle(4,0,5);
 moveto(480,380);
 outtext("Game");
 moveto(490,430);
 outtext("Over");
 moveto(5,5);
 setcolor(4);
 settextstyle(1,0,2);
 if(move_last==1)outtext("You are genius");
 else if(move_last==2)outtext("You are above intelligent");
 else if(move_last==3)outtext("You are intelligent");
 else outtext("You need...more practice");
}
void help(int col)
{
  //.......writing information.........
  moveto(5,5);
  setcolor(col);
  settextstyle(1,0,1);
  outtext("Use arrow keys to move through places......");
  moveto(5,25);
  outtext("Select a piece by enter and then move it by arrow keys....");
  moveto(5,45);
  outtext("Unselect a piece by bkspc.....");
  moveto(5,65);
  outtext("Undo a move by ctr-U");
  moveto(5,85);
  settextstyle(1,0,1);
  setusercharsize(1,2,1,2);
  setcolor(col);
  outtext("Press a key to continue.....");
}
void disp()
{
  //.....erase old things
  setfillstyle(1,11);
  bar(15,418,220,480);
  //......put new things i.e. total moves
  moveto(15,415);
  char str[80];
  sprintf(str,"Total no. of moves....%d",tot);
  setcolor(13);
  settextstyle(1,0,1);
  outtext(str);
  //......and no. of pieces remaining
  moveto(15,435);
  move_last=0;  //.....make it 0 1st to remove its earlier value
  for(int i=0;i<9;i++)for(int j=0;j<9;j++)if(arr[i][j]==1)move_last++;
  sprintf(str,"Marbles left.....%d",move_last);
  outtext(str);
}