#include<iostream.h>
#include<conio.h>
#include<stdio.h>
class account
     {
	     char name[50];
	     int acc_no;
	     char acc_type;
	     int balance;
      public:
	     void initialise(void);
	     void deposit(void);
	     void withdraw(void);
	     void display(void);
	     friend int s_no(int a);
     };
account obj[10];
int k=0,count=0;
int s_no(int a)
{
 for(int j=0;j<10;j++) if(obj[j].acc_no==a) return j;
 return 100;
}

void account::initialise(void)
	       {
		cout<<"Enter name of account holder => ";
		gets(name);
		cout<<"Enter account number => ";
		cin>>acc_no;
		cout<<"Enter account type saving(s) or current(c) => ";
		cin>>acc_type;
		balance = 0;
	       }
void account::deposit(void)
	       {
		int dep;
		cout<<"Amount to be deposited => ";
		cin>>dep;
		if(balance+dep>=1000) balance += dep;
		else {
		      cout<<"Sorry,we require a minimum of 1000 Rs";
		      cout<<"to be put in account.\n";
		      cout<<"Press any key to continue........";
		      getch();
		     }
	       }
void account::withdraw(void)
	       {
		int with;
		char ch;
		cout<<"Amount to be withdrawn => ";
		cin>>with;
		if((balance-with)>=1000)balance-=with;
		else {
		      cout<<"Sorry,we require a minimum of 1000 Rs";
		      cout<<"to be left in account.\n";
		      cout<<"Press any key to continue........";
		      getch();
		     }
	       }
void account::display(void)
	       {
		 k++;
		 cout<<k<<"\t";
		 cout<<acc_no<<"\t  ";
		 cout<<acc_type<<"      ";
		 cout<<balance<<"\t   ";
		 puts(name);
		 fflush(stdout);
		 cout<<"\n";
	       }
 void main()
{
  int choice;
  int i=0,no;
  char ch;
c:clrscr();
  fflush(stdin);
  cout<<"                  MAIN  MENU         \n";
  cout<<"        	   ==========         \n";
  cout<<"  1) ENTER DATA                       \n";
  cout<<"  2) DEPOSIT                          \n";
  cout<<"  3) WITHDRAW                         \n";
  cout<<"  4) DISPLAY RECORD                   \n";
  cout<<"  5) EXIT                             \n";
  cout<<"                                      \n";
  cout<<"  ENTER THE CHOICE (1-5)====>    ";
  cin>>choice;
  switch(choice)
  {
   case 1:{
	    count++;
	    clrscr();
	    cout<<"                     DATA ENTERING MENU     \n";
	    cout<<"                     ==================     \n";
	    for(i=0;i<10;i++)
	       {
		cout<<"             RECORD "<<(i+1)<<"\n";
		cout<<"             =========\n";
		obj[i].initialise();
		cout<<"\n\n";
	       }
	  goto c;
	  }
   case 2:{
	    clrscr();
	  d:cout<<"\n\nEnter account number => ";
	    cin>>no;
	    i=s_no(no);
	    if(i==100){
		      cout<<"Wrong choice.try again(y/n)? ";
		      cin>>ch;
		      if(ch=='y')goto d;
		      else goto c;
		     }
	    else  obj[i].deposit();
	    goto c;
	  }
   case 3:{
	   clrscr();
	   cout<<"\n\nEnter account number => ";
	   cin>>no;
	   i=s_no(no);
	   if(i==100){
		      cout<<"Wrong choice.try again(y/n)? ";
		      cin>>ch;
		      if(ch=='y')goto d;
		      else goto c;
		    }
	   else obj[i].withdraw();
	   goto c;
	  }
  case 4:{
	   if(count==1)
	   {
	   clrscr();
	   cout<<"                        DISPLAY   MENU           \n";
	   cout<<"                        ==============           \n\n\n";
	   cout<<"S.NO.\tAC.NO.\tAC.TYPE\t BALANCE         NAME  \n";
	   cout<<"=====\t======\t=======\t =======   ================\n";
	   for(i=0;i<10;i++) obj[i].display();
	   getch();
	   goto c;
	   }
	   else
	   {
	    clrscr();
	    cout<<"No records have been added.";
	    getch();
	    goto c;
	   }
	 }
   case 5: goto b;
   default:{
	     cout<<"Wrong choice.Try again(y/n)? ";
	     cin>>ch;
	     if(ch=='y')goto c;
	   }
  }
b:;
}