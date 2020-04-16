#include<bios.h>
#include<conio.h>
#include<process.h>
#include<graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include<iostream.h>
#include<string.h>
int count=0;
int mat[8][8];
int check(int mat[8][8]);
inline int retur(int x,int y)
{
 if(x<0||x>7||y<0||y>7)return(0);
 else return(1);
}
void print_mat(int mat[8][8])
{
   count++;
   for(int i=0;i<8;i++)
    {  for(int j=0;j<8;j++)
	  { moveto(120+25+j*50,40+25+i*50);
	    if(mat[i][j]==1)  outtext("Q");
	    else {setcolor(0);outtext("Q");setcolor(10);}
	  }
    }
   gotoxy(1,1);
   cout<<"\nPress any key to see more possibilities or enter to exit....";
   cout<<"\nCount = "<<count<<" ";
   cout<<"\nTotal = 92";
   if(bioskey(0)==7181)exit(0);
}
long int fact(int n)          //...factorial of n
{
 long int fac=1;
 if(n==0)return(1);
 for(int i=1;i<=n;i++)
    fac=fac*i;
 return(fac);
}
//.......here n=8 always
void perm(int *a,const int k,const int n)
{
 if(k==n-1){int t=0;
	    for(int j=0;j<8;j++) //......right
	     {  for(int i=0;i<8;i++)  //......down
		   { if(i==a[t])mat[i][j]=1;
		     else mat[i][j]=0;
		   }
		t++;
	     }
	     //......now the matrix is prepared put it for check
	     if(check(mat))
	     print_mat(mat);
	   }
 else      {  for(int i=k;i<n;i++)
		{  int temp=a[k];a[k]=a[i];a[i]=temp;
		   perm(a,k+1,n);
		   temp=a[k];a[k]=a[i];a[i]=temp;
		}
	   }
}
int check(int mat[8][8])
{
 //........start checking for possibilities
 for(int i=0;i<8;i++)
 for(int j=0;j<8;j++)
 {
     if(mat[i][j]==0)continue;
     //.......means piece is there on (i,j)
	  int x=i,y=j;
	  //.....diagonal checking
	  while(retur(--x,++y))
	    if(mat[x][y])return(0);//....left down
	  x=i,y=j;
	  while(retur(--x,--y))
	    if(mat[x][y])return(0);//....left up
	  x=i,y=j;
	  while(retur(++x,--y))
	    if(mat[x][y])return(0);//....down left
	  x=i,y=j;
	  while(retur(++x,++y))
	    if(mat[x][y])return(0);//....down right
	  x=i,y=j;

	  //.....up,down,right,left checking
	  while(retur(--x,y))
	    if(mat[x][y])return(0);//....up
	  x=i,y=j;
	  while(retur(++x,y))
	    if(mat[x][y])return(0);//....down
	  x=i,y=j;
	  while(retur(x,++y))
	    if(mat[x][y])return(0);//....right
	  x=i,y=j;
	  while(retur(x,--y))
	    if(mat[x][y])return(0);//....left
	  x=i,y=j;
 }
 //.....and at the last when no return(0) encountered or all positions checked
 return(1);
}
void main()
{
   /* request auto detection  */
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
   clearviewport();
   cout<<"Following program illustrates all the possible ways in which\n"
       <<"8 queens can be placed on a chess board in such a way that\n"
       <<"no one can beat anyone.";
   cout<<"\n\n\nA Program by =======>> VIPUL MISTRY AND PRAMOD";
   bioskey(0);
   clearviewport();
   setcolor(10);
   for(int i=1;i<=9;i++)
    { line(70+i*50,40,70+i*50,440);
      line(120,40+(i-1)*50,520,40+(i-1)*50);
    }

   int str[8]={0,1,2,3,4,5,6,7};
   perm(str,0,8);
   clearviewport();
   cout<<"Total possibilities are = "<<count;
   bioskey(0);
   closegraph();
}