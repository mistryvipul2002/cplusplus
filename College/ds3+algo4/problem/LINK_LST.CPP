#include<iostream.h>
#include<process.h>
#include<bios.h>
#include<alloc.h>
#include<stdio.h>
#include<conio.h>
void out()
{
 cout<<"\n\nOut of memory.......";
 cout<<"\nProgram will be aborted......";
 bioskey(0);
 exit(1);
}
//...........union stores three data_types
union data
    {  char c;
       int i;
       float f;
    };
//.......node class instead of struct node
class node
{
	  data info;  //...info can store anyas specified in data defination
	  node *link;
 public:  //....operations on data
	  void getdata(char);
	  void printdata(char);
	  void putdata(node,char);
	  int check_equal(node,char);
	  int check_end(char);
	  //...operations on link
	  node* get_link();
	  void set_link(node*);
	  void getnode();
};
//....defination of all the functions related to data
void node::getdata(char d_type)
{
 switch(d_type)
 { case 'c':cin>>info.c;break;
   case 'i':cin>>info.i;break;
   case 'f':cin>>info.f;break;
 }
 link=NULL;
}
void node::printdata(char d_type)
{
 switch(d_type)
 { case 'c':cout<<info.c;break;
   case 'i':cout<<info.i;break;
   case 'f':cout<<info.f;break;
 }
}
void node::putdata(node T,char d_type)
{
 switch(d_type)
 { case 'c':info.c=T.info.c;break;
   case 'i':info.i=T.info.i;break;
   case 'f':info.f=T.info.f;break;
 }
}
int node::check_equal(node T,char d_type)
{
 switch(d_type)
 { case 'c':if(T.info.c==info.c)return(1);else return(0);
   case 'i':if(T.info.i==info.i)return(1);else return(0);
   case 'f':if(T.info.f==info.f)return(1);else return(0);
 }
 return(1);
}
//....check if terminating value is entered or not
int node::check_end(char d_type)
{
 switch(d_type)
 { case 'c':if(info.c=='#')return(1);else return(0);
   case 'i':if(info.i==-999)return(1);else return(0);
   case 'f':if(info.f==-999)return(1);else return(0);
 }
 return(1);
}
//....definations of functions of link
void node::set_link(node *New)
{ link =New;
}
node * node::get_link()
{   return(link);
}
void node::getnode()
{ link = new node;
  if(!link)out();
}
//.....node class over
class list
{         node *Start;
	  char data_type;//..this variable tells the type of data stored in list
  public: list();             //...constructor
	  void create();
	  void traverse();
	  void search();
	  void del(int);     //...delete element at pos
	  void dele();       //...intractive function
	  int ins(int,node); //...insert element of node at int
	  void insert();     //...intractive function
	  int count();       //...count total nodes
	  void destroy_list();  //....destroys all pointers
	  void getlist();   //....getlist
};
//....definations of functions
list::list()
{ Start=NULL;
  data_type='c';
}
void list::create()
{
 clrscr();

ag: cout<<"Enter type of data you want to enter ?\n";
    cout<<"c-character, f-float, i-integer ? ";
    cin>>data_type;

 if(data_type!='c'&&data_type!='i'&&data_type!='f')
    { cout<<"Wrong data type.......";goto ag;}

 cout<<"\nEnter the elements of list ? \n";

 switch(data_type)
 { case 'c': cout<<"Enter # to finish:-\n";break;
   case 'i': cout<<"Enter -999 to finish:-\n";break;
   case 'f': cout<<"Enter -999 to finish:-\n";break;
 }
 node *Next;
 int counter=0;

 //...execute following infinite loop
 while(1)
 {
 node in_node;
 in_node.getdata(data_type);  //.....enter data from user and store in in_node
 if(!in_node.check_end(data_type))       //...if terminating value is not entered
    {
      if(counter==0)      //.....if first node is being created
	   {
	     Next->getnode();   //...dynamically allocate space for Next
	     Start=Next;        //..store initial address in Start
	     Next->putdata(in_node,data_type);//...put value entered into Next
	   }
      else { Next->get_link()->getnode();
	     Next = Next->get_link();
	     Next->putdata(in_node,data_type);
	   }
    }
 else   //..if terminating value is there
    { if(counter==0)Start=NULL;//.....if initial node is terminating put
			       //....Start as NULL i.e. list of length 0
      else Next->set_link(NULL);    //...make last pointer as NULL
      return;    //...return from function
    }
 counter=1;     //....change counter so that value of Start do not change
 }  //..end of while loop

}
void list::traverse()
{
 clrscr();
 cout<<"The list you entered is :-\n";
 getlist();
 cout<<"\nPress any key to continue......";
 bioskey(0);
}
void list::search()
{
 clrscr();
 cout<<"Enter the item to be searched ?";
 node T;
 T.getdata(data_type);
 cout<<"\nList :- \n";
 getlist();
 cout<<"\n\n";
 node *Next=Start;
 int loc=0,found=0;
 while(Next)
 {loc++;
  if(T.check_equal(*Next,data_type))
    { found=1;  //put it 1 means at least one location is searched
      cout<<"\nItem ";
      T.printdata(data_type);
      cout<<" found at location "<<loc;
    }
  Next=Next->get_link();
 }

 if(found==0){ cout<<"\nItem ";
	       T.printdata(data_type);
	       cout<<" not found.";
	     }
 cout<<"\n\nPress any key to return to main menu......";
 bioskey(0);
}
void list::del(int pos)
{
 node *Next=Start;
 int loc=0;
 while(Next)
 { loc++;        //..Next is pointing to loc position in list
   if(loc==pos-1)    //....Next "points" to pos-1 position
	 { node *Temp= Next->get_link(); //...store address of pos element in Temp
	   Next->set_link(Next->get_link()->get_link());
	   delete(Temp);   //....and now delete element at pos
	 }
   Next=Next->get_link();
 }
}
void list::dele()
{
 clrscr();
 cout<<"List :-\n";
 getlist();
 cout<<"\nEnter the position to be deleted ?";
 int pos;cin>>pos;

 if(pos>count())
   {  cout<<"\nOut of range........";
      bioskey(0);
      return;
   }

 del(pos);
 cout<<"Item deleted successfully...\n";

 cout<<"\nList :-\n";
 getlist();
 cout<<"\n\nPress any key to return to main menu......";
 bioskey(0);
}
int list::ins(int pos,node T)
{
 node *Next=Start;
 int loc=0;
 while(Next)
 { loc++;        //..Next is pointing to loc position in list
   if(loc==pos-1)    //....Next "points" to pos-1 position
    { node *Temp=Next->get_link();  //....and address of pos element is stored in
	  //....link part of pos-1 element "to which" Next points to presently
	  //...hence store address of pos position in Temp
      Next->getnode();      //....Next now points to new element

      if(!Next->get_link())       //....if not enough memory
	 {  Next->get_link()->set_link(Temp);  //....restore its link value
	    return(0);        //...and return 0
	 }

      Next =Next->get_link();   //..make Next point to new element created
      Next->putdata(T,data_type);  //....put data in new element
      Next->set_link(Temp);//....in link of new element put earlier address
      return(1);
    }
   Next=Next->get_link();
 }
 return(1);
}
void list::insert()
{
 clrscr();
 cout<<"List :-\n";
 getlist();
 cout<<"\nEnter the data to be inserted ?";
 node T;
 T.getdata(data_type);
 cout<<"\nEnter the position to be inserted ?";
 int pos;cin>>pos;

 if(pos>count()+1)
   {  cout<<"\nOut of range........";
      bioskey(0);
      return;
   }

 if(ins(pos,T)==0)  //...insertion unsuccessful
    cout<<"Item cannot be inserted...\n";
 else cout<<"Item inserted successfully...\n";

 cout<<"\nList :-\n";
 getlist();
 cout<<"\n\nPress any key to return to main menu......";
 bioskey(0);
}
int list::count()
{
 node *Next=Start;
 int loc=0;
 while(Next)
  { loc++;
    Next=Next->get_link();
  }
 return(loc);
}
void list::destroy_list()
{
 node *Next=Start;
 while(Start)
 { Next=Next->get_link();
   delete(Start);
   Start=Next;
 }
}
void list::getlist()
{
 node* Next=Start;
 while(Next)
  { Next->printdata(data_type);
    cout<<" ";   //(char)219;
    Next =Next->get_link();
  }
}
//....class 'list' over
void main()
{
 int flag=0;  //...to determine if list exit or not
 list list1;    //..create a linked list

again: clrscr();
 cout<<"\n\n\n\t\t\tLinked List Program by Vipul Mistry"
     <<"\n\n\n\t\t1) Create List\n\t\t"
	       <<"2) Traverse List\n\t\t"
	       <<"3) Search an item\n\t\t"
	       <<"4) Insert item\n\t\t"
	       <<"5) Delete item\n\t\t"
	       <<"6) Count Nodes\n\t\t"
	       <<"7) Exit\n\n";
 cout<<"\tPress your choice......";
begin:switch(bioskey(0))
 { case 561: if(flag)       //....means list has already been created
	     { clrscr();
	       cout<<"List already exists. Want to create new(y/n)?";
	       char f;cin>>f;
	       if(f!='y')goto again;
	     }
	     if(flag!=0)list1.destroy_list(); //...destroy earlier list
	     list1.create();//..create linked list
	     flag=1; //...change the value of flag as list has been created
	     goto again;
   case 818: list1.traverse(); //.....traverse the list
	     goto again;
   case 1075:list1.search();
	     goto again;
   case 1589:list1.dele();
	     goto again;
   case 1332:list1.insert();
	     goto again;
   case 1846:clrscr();
	     cout<<"Total number of nodes are :-\n\n";
	     cout<<list1.count();
	     bioskey(0);
	     goto again;
   case 2103:break; //....exit the program
   default:  goto begin;
 }
 list1.destroy_list();
}