#include<process.h>
#include<iostream.h>
#include <conio.h>
#include<graphics.h>
#include<bios.h>
#define Maxsize 50
void print(int base,int aux,int des,int dis);
int disks,spc,D_ht;
/***********************************************************/
class stack
{        int array[Maxsize];
			int top;
  public:int numb;
			stack();
			int pop();
			void push(int);
			int gettop();
}stk[3];
stack::stack()
{   for(int i=0;i<Maxsize;i++)array[i]=0;
	 top=-1;
}
int stack::gettop()
{return(array[top]);}
int stack::pop()
{ int cntr=160*(1+numb);
  int top_leftx=cntr-spc*array[top];
  int top_lefty=380-(top+1)*D_ht;
  setcolor(0);
  line(top_leftx,top_lefty,2*cntr-top_leftx,top_lefty);
  line(top_leftx,top_lefty,top_leftx,top_lefty+D_ht-1);
  line(2*cntr-top_leftx,top_lefty,2*cntr-top_leftx,top_lefty+D_ht-1);
  setcolor(10);
  line(cntr,top_lefty,cntr,top_lefty+D_ht);
  return(array[top--]);
}
void stack::push(int n)
{ setcolor(10);
  int cntr=160*(1+numb);
  int top_leftx=cntr-spc*n;
  int top_lefty=380-(top+2)*D_ht;
  rectangle(top_leftx,top_lefty,2*cntr-top_leftx,top_lefty+D_ht);
  setcolor(0);
  line(cntr,top_lefty+1,cntr,top_lefty+D_ht-1);
  setcolor(10);
  array[++top]=n;
}
/***********************************************************/
void main()
{ /* request auto detection  */
  int gdriver = DETECT, gmode;
  /* initialize graphics and local variables */
  initgraph(&gdriver, &gmode, "\\tc\\bgi");
  clearviewport();
  stk[0].numb=0;stk[1].numb=1;stk[2].numb=2;
  cout<<"\n\t\tTower of Hanoi\n";
  cout<<"\t\t==============\n\n";
  cout<<"Enter the number of disks (maximum 20) ? ";
  cin>>disks;
  cout<<"\nPress enter to stop execution of program.......";
  bioskey(0);
  clearviewport();
  gotoxy(25,2);cout<<"Tower of Hanoi\n";
  gotoxy(25,3);cout<<"==============\n";
  gotoxy(18,4);cout<<"Made by---> Vipul Mistry\n\n";
  setcolor(10);
  D_ht=250/disks;
  spc=75/disks;
	  line(50,380,590,380);  //....hori line
	  line(320,100,320,380);  //...pole 2
	  line(480,100,480,380);  //...pole 3
	  line(160,100,160,380-D_ht*disks);    //....pole 3
  for(int i=disks;i>=1;i--)stk[0].push(i);
  bioskey(0);
  print(1,2,3,disks);
  closegraph();
}
void print(int base,int aux,int des,int dis)
{ if(dis==1)
	{ stk[des-1].push(stk[base-1].pop());
	  gotoxy(20,25);
	  cout<<"Move disk "<<stk[des-1].gettop()<<" from pole "<<base<<" to pole "<<des<<"\n";
	  if(bioskey(0)==7181)exit(1);
	  return;
	}
  print(base,des,aux,dis-1);
  stk[des-1].push(stk[base-1].pop());
  gotoxy(20,25);
  cout<<"Move disk "<<stk[des-1].gettop()<<" from pole "<<base<<" to pole "<<des<<"\n";
  if(bioskey(0)==7181)exit(1);
  print(aux,base,des,dis-1);
}