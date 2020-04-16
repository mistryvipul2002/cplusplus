#include<iostream.h>
#include<bios.h>
#include<conio.h>
#define Maxsize 10
#define Max_pri 10
class queue
{        int array[Maxsize];
	 int front;
	 int rear;
	 int empty;
 public: queue();
	 int qinsert(int);
	 int qdelete();
	 void create();
	 int getnext(int);
	 void display();
	 int isempty();
	 friend void display(queue*);
};
queue::queue()
{ front=rear=0;empty=1;}
int queue::isempty()
{ if(empty)return(1);
  else return(0);
}
int queue::getnext(int n)
{ if(n==Maxsize-1)return(0);
  else return(n+1);
}
int queue::qinsert(int n)
{ if(front==getnext(rear))return(0);
  if(empty){array[rear]=n;empty=0;return(1);}
  empty=0;   //...list not empty
  rear=getnext(rear);
  array[rear]=n;
  return(1);
}
int queue::qdelete()
{ if(empty){cout<<"\nJob Underflow.........";return(0);}
  if(!empty&&front==rear){empty=1;return(1);}
  front=getnext(front);
  if(front==rear)empty=0;
  return(1);
}
void queue::create()
{ int n=0,i=1;
  while(1)
  { cout<<i++<<") Enter info (enter -999 to end).....";cin>>n;
    if(n==-999)break;
    if(!qinsert(n)){ bioskey(0);break;}
  }
}
void display(queue q[])
{  for(int i=Max_pri;i>=0;i--)
    { if(!q[i].isempty())
      {	  int j=q[i].front;
	  while(1)
	  { if(j==q[i].rear)break;
	    cout<<"("<<i+1<<","<<q[i].array[j]<<") ";
	    j=q[i].getnext(j);
	  }
	  cout<<"("<<i+1<<","<<q[i].array[j]<<") ";
      }
    }
}
void main()
{ clrscr();
  cout<<"\n\n\t\t\tPriority Queue\n\n";
  queue q[Max_pri];     //.....make two dim array
  cout<<"Priority = 1-"<<Maxsize<<"   Maximum jobs/priority ="<<Maxsize<<"\n";
  cout<<"To end the list enter the number as -999\n\n";
  int i=1;
  while(1)
  { int n,pr;
    cout<<i++<<") Priority and Number....";cin>>pr>>n;
    if(n==-999)break;
    if(pr>Max_pri){cout<<"\nPriority Overflow........\n";continue;}
    if(!q[pr-1].qinsert(n))cout<<"\nJob Overflow for priority "<<pr<<"\n";
  }
a:clrscr();
  cout<<"Priority Queue :-";
  cout<<"\tPriority = 1-"<<Maxsize<<"   Maximum jobs/priority ="<<Maxsize<<"\n";
  cout<<"Front----------------Rear\n"
      <<"(Priority,Job Number):-\n";
  display(q);
  cout<<"\n\n";
  cout<<"\t\t\t1) Insert\n";
  cout<<"\t\t\t2) Delete\n";
  cout<<"\t\t\t3) Quit\n";
  cout<<"\t\tPress your choice........";
  char ch;cin>>ch;
  switch(ch)
  { case '1':int n,pr;
	     cout<<"\nEnter priority and number to be inserted.......";
	     cin>>pr>>n;
	     if(pr>Max_pri){cout<<"\nPriority Overflow........\n";bioskey(0);goto a;}
	     if(!q[pr-1].qinsert(n)){cout<<"\nJob Overflow for priority "<<pr<<"\n";bioskey(0);}
	     goto a;
    case '2':for(i=Max_pri;i>=0;i--)
	      if(!q[i].isempty())
	       {q[i].qdelete();break;}
	     goto a;
    default:break;
  }
}