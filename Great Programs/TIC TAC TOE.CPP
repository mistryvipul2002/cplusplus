#include<bios.h>
#include <graphics.h>
#include<dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<iostream.h>
const int move[19]={1,2,3,4,5,6,14,15,16,17,18,19,20,21,22,23,24,25,65};
int pos[9]={1,2,3,4,5,6,7,8,9};
int pl1_pos[6]={0,0,0,0,0,0};
int pl2_pos[6]={0,0,0,0,0,0};
int p=0,q=0;
int safety=0;
class game {
	    private:
		   int pl1_move,pl2_move;
	    public:void help();
		   int option(int a,int b);
		   void player_choose();
		   int check(int x,int y);
		   int check1(int);
		   int check2(int,int);
		   void play();
	   };
void game::help()
{
 setcolor(12);
 settextstyle(4,0,4);
 moveto(190,10);
 outtext("About the game");
 setlinestyle(0,0,3);
 line(190,53,408,53);
 setlinestyle(0,0,0);
 moveto(60,60);
 settextstyle(1,0,3);
 setcolor(14);
 outtext("Tic Tac Toe");
 setcolor(9);
 outtext(" is a game of 2 Players. In this game");
 moveto(3,90);
 outtext("players will get chance one by one. Press the number");
 moveto(3,120);
 outtext("of a place to put your move at that position. Once");
 moveto(3,150);
 outtext("the move has been placed,that place gets locked up");
 moveto(3,180);
 outtext("i.e. no other move can take that position.");
 moveto(60,220);
 outtext("There are 9 places to be filled. The player wins");
 moveto(3,250);
 outtext("the game if he could manage any of his three moves");
 moveto(3,280);
 outtext("in the same line- horizontal,vertical or diagonal.");
 moveto(3,450);
 outtext("              Press any key to continue.......");
 moveto(3,368);
 setcolor(14);
 outtext("A Game by - Vipul Mistry (Student of B.Tech,ISM)");
 moveto(3,393);
 outtext("Prepared on - 3rd January 2001");
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
 getch();getch();
}
void game::play()
{
			       setcolor(10);
			       line(280,40,280,280);
			       line(360,40,360,280);
			       line(200,120,440,120);
			       line(200,200,440,200);
			       settextstyle(1,0,1);
			       moveto(200,40);outtext("1");
			       moveto(289,40);outtext("2");
			       moveto(369,40);outtext("3");
			       moveto(200,120);outtext("4");
			       moveto(289,120);outtext("5");
			       moveto(369,120);outtext("6");
			       moveto(200,200);outtext("7");
			       moveto(289,200);outtext("8");
			       moveto(369,200);outtext("9");
			       int turn=1;//means player1
			       moveto(225,300);
			       settextstyle(1,0,6);
			       setcolor(12);
			       outtext("Player");
			       moveto(130,380);
			       settextstyle(1,0,3);
			       outtext("Press the position of your move");
			       settextstyle(1,0,6);

			 start:int counter=0;
			       moveto(401,300);
			       setcolor(12);
			       settextstyle(1,0,6);
			       if(turn==1)outtext("1");
			       else outtext("2");
			       int y=bioskey(0);
			       switch(y)
			       { case 561 :counter=check(turn,1);break;
				 case 818 :counter=check(turn,2);break;
				 case 1075:counter=check(turn,3);break;
				 case 1332:counter=check(turn,4);break;
				 case 1589:counter=check(turn,5);break;
				 case 1846:counter=check(turn,6);break;
				 case 2103:counter=check(turn,7);break;
				 case 2360:counter=check(turn,8);break;
				 case 2617:counter=check(turn,9);break;
				 default:  goto start;
			       }
			       moveto(401,300);
			       setcolor(0);
			       if(turn==1)outtext("1");
			       else outtext("2");

			       if(counter!=0)
			       {
				 if(turn==1)turn=2;
				 else turn=1;
			       }
			       goto start;
}
int game::check(int x,int y)
{
 if(pos[y-1]==0)return(0);
 else {
       if(y>=1 && y<=3)
       gotoxy(30+(y-1)*10,6);
       else if(y>=4 && y<=6)
	    gotoxy(30+(y-1-3)*10,11);
	    else if(y>=7 && y<=9)
		 gotoxy(30+(y-1-6)*10,16);
       if(x==1)cout<<(char)move[pl1_move-1];
       else cout<<(char)move[pl2_move-1];
       pos[y-1]=0;
      }
 if(x==1)pl1_pos[p++]=y;  //....p and q are 0 initially
 else pl2_pos[q++]=y;
 if(check1(x)==1)     //.....if this player has won
		{
		 moveto(225,300);
		 settextstyle(1,0,6);
		 setcolor(0);
		 outtext("Player");
		 moveto(130,380);
		 settextstyle(1,0,3);
		 outtext("Press the position of your move");
		 settextstyle(1,0,6);
		 moveto(401,300);
		 settextstyle(1,0,6);
		 if(x==1)outtext("1");
		 else outtext("2");

		 settextstyle(1,0,7);
		 setcolor(11);
		 moveto(210,280);
		 outtext("Player ");
		 if(x==1)outtext("1");
		 else outtext("2");
		 moveto(270,360);
		 outtext("Won");
		 getch();getch();
		 clearviewport();
		 setcolor(10);
		 moveto(200,100);
		 settextstyle(1,0,6);
		 outtext("Thank");
		 moveto(240,200);
		 outtext("You");
		 delay(500);
		 closegraph();
		 exit(0);
		}
 if(check1(x)==-1)
		{
		 moveto(225,300);
		 settextstyle(1,0,6);
		 setcolor(0);
		 outtext("Player");
		 moveto(130,380);
		 settextstyle(1,0,3);
		 outtext("Press the position of your move");
		 settextstyle(1,0,6);
		 moveto(401,300);
		 settextstyle(1,0,6);
		 if(x==1)outtext("1");
		 else outtext("2");

		 settextstyle(1,0,7);
		 setcolor(11);
		 moveto(220,280);
		 outtext("Game");
		 moveto(240,360);
		 outtext("Draw");
		 getch();getch();
		 clearviewport();
		 setcolor(10);
		 moveto(200,100);
		 settextstyle(1,0,6);
		 outtext("Thank");
		 moveto(240,200);
		 outtext("You");
		 delay(500);
		 closegraph();
		 exit(0);
		}
 return(1);
}
int game::check1(int pl)    //.....takes the player number as argument
{
 safety=0;
 for(int u=0;u<9;u++)if(pos[u]!=0)safety=1;
 if(check2(pl,1)==1 && check2(pl,2)==1 && check2(pl,3)==1 )
	{ line(240,80,240+80+80,80);return(1); }
 if(check2(pl,4)==1 && check2(pl,5)==1 && check2(pl,6)==1 )
	{ line(240,80+80,240+80+80,80+80);return(1); }
 if(check2(pl,7)==1 && check2(pl,8)==1 && check2(pl,9)==1 )
	{ line(240,80+80+80,240+80+80,80+80+80);return(1); }
 if(check2(pl,1)==1 && check2(pl,4)==1 && check2(pl,7)==1 )
	{ line(200+40,80,200+40,80+80+80);return(1); }
 if(check2(pl,2)==1 && check2(pl,5)==1 && check2(pl,8)==1 )
	{ line(200+40+80,80,200+40+80,80+80+80);return(1); }
 if(check2(pl,3)==1 && check2(pl,6)==1 && check2(pl,9)==1 )
	{ line(200+40+80+80,80,200+40+80+80,80+80+80);return(1); }
 if(check2(pl,1)==1 && check2(pl,5)==1 && check2(pl,9)==1 )
	{ line(200+40,80,200+40+80+80,80+80+80);return(1); }
 if(check2(pl,3)==1 && check2(pl,5)==1 && check2(pl,7)==1 )
	{ line(200+40,80+80+80,200+40+80+80,80);return(1); }

 if(safety==0)return(-1);//....means all positions are occupied
			 //....and none has won
 return(0);//....the player donot won since no series of number found
}
int game::check2(int tur,int numb)//...check if number 'numb' is present in
{                                 //...position array of player number 'tur'
 for(int j=0;j<6;j++)
     {
      if(tur==1)
	{ if(pl1_pos[j]==numb)return(1); }
      if(tur==2)
	{ if(pl2_pos[j]==numb)return(1); }
     }
 return(0);
}
int game::option(int a,int b)
{
   int i;
   gotoxy(a,b);
   for(i=0;i<=18;i++)cout<<(char)move[i]<<"  ";
   setcolor(10);int num=1;
   rectangle((a-1)*8-2,(b-1)*16-2,a*8+1,b*16+1);
beg:int c=bioskey(0);
   switch(c)
      {
       case 19712  :setcolor(0);
		    rectangle((a-1+((num-1)*3))*8-2,(b-1)*16-2,
				(a+((num-1)*3))*8+1,b*16+1);
		    if(num==19)num=1;
		    else num++;
		    setcolor(10);
		    rectangle((a-1+((num-1)*3))*8-2,(b-1)*16-2,
				(a+((num-1)*3))*8+1,b*16+1);
		    goto beg;
       case  7181  :break;
       case 19200  :setcolor(0);
		    rectangle((a-1+((num-1)*3))*8-2,(b-1)*16-2,
				(a+((num-1)*3))*8+1,b*16+1);
		    if(num==1)num=19;
		    else num--;
		    setcolor(10);
		    rectangle((a-1+((num-1)*3))*8-2,(b-1)*16-2,
				(a+((num-1)*3))*8+1,b*16+1);
		    goto beg;
       default:     goto beg;
      }
return(num);
}
void game::player_choose()
{
 setcolor(12);
 settextstyle(1,0,3);
 moveto(150,54);
 outtext("Player1");
 moveto(150,88);
 outtext("Choose your move");
 pl1_move = option(20,9);

 moveto(150,170);
 setcolor(12);
 outtext("Player2");
 moveto(150,204);
 outtext("Choose your move");
again: pl2_move = option(20,17);
 if(pl1_move==pl2_move){
			setcolor(4);
			settextstyle(1,0,2);
			moveto(180,320);
			outtext("Please select a different move.......");
			getch();getch();
			setcolor(0);
			moveto(180,320);
			outtext("Please select a different move.......");
			setcolor(0);
			rectangle((20-1+((pl2_move-1)*3))*8-2,(17-1)*16-2,
				     (20+((pl2_move-1)*3))*8+1,17*16+1);
			goto again;
		       }
 clearviewport();
}
void main(void)
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

   settextstyle(1,0,16);
   moveto(40,20);
   setusercharsize(5,1,5,1);
   setcolor(10);
   outtext("Tic Tac");
   moveto(170,190);
   outtext("Toe");

   delay(2000);
   clearviewport();
   game g1;
   g1.help();
   clearviewport();
   g1.player_choose();
   g1.play();
}

