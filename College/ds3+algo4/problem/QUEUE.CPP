#include<iostream.h>
#include<bios.h>
#include<conio.h>
#define Maxsize 30
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
};
queue::queue()
{ front=rear=0;empty=1;}
void queue::display()
{ if(empty){cout<<"Queue empty";return;}
  cout<<"Front---------------Rear";
  cout<<"\nFront = "<<front<<"\tRear = "<<rear<<"\n";
  for(int i=front;i<=rear;i=getnext(i))
     cout<<array[i]<<"  ";
}
int queue::getnext(int n)
{ if(n==Maxsize-1)return(0);
  else return(n+1);
}
int queue::qinsert(int n)
{ if(front==getnext(rear)){cout<<"\nOverflow............";return(0);}
  if(empty){array[rear]=n;empty=0;return(1);}
  empty=0;   //...list not empty
  rear=getnext(rear);
  array[rear]=n;
  return(1);
}
int queue::qdelete()
{ if(empty){cout<<"\nUnderflow.........";return(0);}
  if(!empty&&front==rear){empty=1;return(1);}
  front=getnext(front);
  if(front==rear)empty=0;
  return(1);
}
void queue::create()
{ int n=0;
  while(1)
  { cout<<"Enter info (enter -999 to end).....";cin>>n;
    if(n==-999)break;
    qinsert(n);
  }
}
void main()
{ clrscr();
  cout<<"\n\n\t\t\tPriority Queue\n";
  cout<<"Create Priority Queue........\n";
  queue q;
  q.create();
a:  clrscr();
  q.display();cout<<"\n\n";
  cout<<"\t\t\t1) Insert\n";
  cout<<"\t\t\t2) Delete\n";
  cout<<"\t\t\t3) Quit\n";
  cout<<"\t\tPress ur choice........";
  char ch;cin>>ch;
  switch(ch)
  { case '1':cout<<"\nEnter wht is to insert.......";int n;cin>>n;
	     q.qinsert(n);
	     q.display();
	     bioskey(0);
	     goto a;
    case '2':if(q.qdelete())
	     q.display();
	     bioskey(0);
	     goto a;
    default:break;
  }
}