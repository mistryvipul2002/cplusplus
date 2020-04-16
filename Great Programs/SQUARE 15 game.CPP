#include<stdlib.h>
#include<iostream.h>
#include<time.h>
#include<bios.h>
#include<dos.h>
#include<conio.h>
int xbl,ybl;
int arr[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
void print_square();
void random_print(int dif)
{
 //...put reverse gear
 xbl=ybl=3;
 int cou=0;
 for(int i=0;i<4;i++)for(int j=0;j<4;j++)arr[i][j]=++cou;
 print_square();
 randomize();
 int time =700;
 int steps=50*dif;
 for(i=1;i<=steps;i++)
 {
  if(time-50<=0)time=5;
  else time-=50;
  switch(random(4)+1)
   {
    case 1://...to move right
	   if(ybl-1<=3&&ybl-1>=0)
	     {
	      gotoxy(24+ybl*7,8+xbl*2);
	      cout<<arr[xbl][ybl-1];
	      gotoxy(24+(ybl-1)*7,8+xbl*2);
	      cout<<"  ";delay(time);
	      arr[xbl][ybl]=arr[xbl][ybl-1];
	      arr[xbl][ybl-1]=0;
	      ybl--;
	     }
	   break;
    case 2://...to move left
	   if(ybl+1<=3&&ybl+1>=0)
	     {
	      gotoxy(24+ybl*7,8+xbl*2);
	      cout<<arr[xbl][ybl+1];
	      gotoxy(24+(ybl+1)*7,8+xbl*2);
	      cout<<"  ";delay(time);
	      arr[xbl][ybl]=arr[xbl][ybl+1];
	      arr[xbl][ybl+1]=0;
	      ybl++;
	     }
	   break;
    case 3://...to move up
	   if(xbl+1<=3&&xbl+1>=0)
	     {
	      gotoxy(24+ybl*7,8+xbl*2);
	      cout<<arr[xbl+1][ybl];
	      gotoxy(24+ybl*7,8+(xbl+1)*2);
	      cout<<"  ";delay(time);
	      arr[xbl][ybl]=arr[xbl+1][ybl];
	      arr[xbl+1][ybl]=0;
	      xbl++;
	     }
	   break;
    case 4://...to move down
	   if(xbl-1<=3&&xbl-1>=0)
	     {
	      gotoxy(24+ybl*7,8+xbl*2);
	      cout<<arr[xbl-1][ybl];
	      gotoxy(24+ybl*7,8+(xbl-1)*2);
	      cout<<"  ";delay(time);
	      arr[xbl][ybl]=arr[xbl-1][ybl];
	      arr[xbl-1][ybl]=0;
	      xbl--;
	     }
   }//.....end of switch
 }//....end of for
}
void print_square()
{
 //....print square
 for(int i=0;i<=3;i++)
  for(int j=0;j<=3;j++)
   {
    gotoxy(24+j*7,8+i*2);
    if(arr[i][j]!=0)cout<<arr[i][j];
//    else {xbl=i;ybl=j;}
   }
}
int check()
{
 int cou=0;
 for(int i=0;i<=3;i++)
  { for(int j=0;j<=3;j++)
    { if(i==3&&j==3)continue;
      else {if(arr[i][j]!=++cou)return(0);}
    }
  }
 return(1);
}
void main()
{
 clrscr();
 cout<<"Enter the difficulty level (1-10) ?";
 int diff;cin>>diff;
 main:clrscr();
 cout<<"\n\n\n		A Game by Vipul Mistry\n\n\n";
 cout<<"\n\n\n\n\n\n\n\n\n\n\t\tUse arrow keys to move the numbers...";
 cout<<"\n\n\t\tPress enter to exit the game..";
 int tot_mov=0;
 gotoxy(1,22);
 cout<<"\t\tWait....";
 random_print(diff);
 gotoxy(1,22);
 cout<<"\t\t\tPlay...";
 gotoxy(24+ybl*7,8+xbl*2);
 beg:int no=bioskey(0);
 switch(no)
 {
     case 19712://...to move right
	   if(ybl-1<=3&&ybl-1>=0)
	     {
	      gotoxy(24+ybl*7,8+xbl*2);
	      cout<<arr[xbl][ybl-1];
	      gotoxy(24+(ybl-1)*7,8+xbl*2);
	      cout<<"  ";
	      arr[xbl][ybl]=arr[xbl][ybl-1];
	      arr[xbl][ybl-1]=0;
	      ybl--;tot_mov++;
	      if(check()==1)goto end;
	     }
	     goto beg;
    case 19200://...to move left
	   if(ybl+1<=3&&ybl+1>=0)
	     {
	      gotoxy(24+ybl*7,8+xbl*2);
	      cout<<arr[xbl][ybl+1];
	      gotoxy(24+(ybl+1)*7,8+xbl*2);
	      cout<<"  ";
	      arr[xbl][ybl]=arr[xbl][ybl+1];
	      arr[xbl][ybl+1]=0;
	      ybl++;tot_mov++;
	      if(check()==1)goto end;
	     }
	     goto beg;
    case 18432://...to move up
	   if(xbl+1<=3&&xbl+1>=0)
	     {
	      gotoxy(24+ybl*7,8+xbl*2);
	      cout<<arr[xbl+1][ybl];
	      gotoxy(24+ybl*7,8+(xbl+1)*2);
	      cout<<"  ";
	      arr[xbl][ybl]=arr[xbl+1][ybl];
	      arr[xbl+1][ybl]=0;
	      xbl++;tot_mov++;
	      if(check()==1)goto end;
	     }
	   goto beg;
    case 20480://...to move down
	   if(xbl-1<=3&&xbl-1>=0)
	     {
	      gotoxy(24+ybl*7,8+xbl*2);
	      cout<<arr[xbl-1][ybl];
	      gotoxy(24+ybl*7,8+(xbl-1)*2);
	      cout<<"  ";
	      arr[xbl][ybl]=arr[xbl-1][ybl];
	      arr[xbl-1][ybl]=0;
	      xbl--;tot_mov++;
	      if(check()==1)goto end;
	     }
	    goto beg;
 case 7181:goto next;
 default:  goto beg;
 }
end:clrscr();
 cout<<"\n\n\n You win.....";
 goto t;
 next:clrscr();
 t:cout<<"\n\n\n Total number of moves = "<<tot_mov;
 cout<<"\n\nThank you for playing...\n";
 cout<<"Want to play again(y/n)?";
 char ch;cin>>ch;
 if(ch=='y'||ch=='Y')goto main;
}