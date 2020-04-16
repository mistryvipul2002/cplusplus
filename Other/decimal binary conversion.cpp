#include<iostream.h>
#include<conio.h>
void main()
{
start: clrscr();int ch;
 cout<<"                            MAIN MENU                     \n";
 cout<<"                            =========                   \n\n\n";
 cout<<"       ( 1 ) Convert binary to decimal             \n";
 cout<<"       ( 2 ) Convert decimal to binary                 \n";
 cout<<"       ( 3 ) EXIT                \n\n\n\n\n";
 cout<<"      Enter your choice======>   ";
 cin>>ch;
 switch(ch)
 {
  case 1: clrscr();
	  long int num;int prod =1,sum=0,dig;
	  cout<<"Enter the binary nummber=====>  ";
	  cin>>num;
	  if(num<0)
	  {
	     cout<<"Wrong number.........";
	     getch();
	     goto start;
	  }
	  if(num==0)cout<<"Decimal equivalent is ======> 0";
	  else
	  {
		do
		{
		   dig = num%10;
		   if((dig!=0)&&(dig!=1))
			 {
			   cout<<"Wrong number.........";
			   getch();
			   goto start;
			 }
		  num /= 10;
		  sum+=dig*prod;
		  prod*=2;
		}
	  while(num);
	  cout<<"Decimal equivalent is ======>"<<sum;
	  }
	  getch();
	  goto start;
  case 2: clrscr();
	  int n=0,no[100];long long dec;
	  cout<<"Enter the decimal number====>  ";
	  cin>>dec;
	  if(dec<0)
	  {
	     cout<<"Wrong number.........";
	     getch();
	     goto start;
	   }
	  cout<<"Binary equivalent is = ";
	  if(dec==0)cout<<0;
	  else
	   {
	      while(dec)
		 {
		  no[n]=dec%2;
		  n++;
		  dec /= 2;
		 };
	      for(int i=(n-1);i>=0;i--)cout<<no[i];
	   }
	  getch();
	  goto start;
  case 3: break;
  default: cout<<"\n\nWrong choice.........\n";
	   cout<<"\n\nPress any key to continue.............";
	   getch();
	   goto start;
 }
}
