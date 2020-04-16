#include<bios.h>
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
int day(long int dd1,long int mm1,long int yy1);
void main()
{
 int m_array[12]={31,28,31,30,31,30,31,31,30,31,30,31};
 char month[12][10]={"January","February","March","April","May","June",
	   "July","August","September","October","November","December"};
 int mm,yy;
start:clrscr();
 cout<<"\n\n                    Millenium Calendar\n";
 cout<<"                    ==================\n";
 cout<<"\n             Brought to you by Vipul Mistry";
 cout<<"\n\n\n";
 cout<<"             Options\n";
 cout<<"             -------\n\n";
 cout<<"          1) Monthly Calendar\n";
 cout<<"          2) Exit\n\n\n\n";
 cout<<"        Press your choice..............";
 switch(bioskey(0))
 {
  case 561:a:clrscr();
	  cout<<"\n\n\nEnter the month ? ";
	  cin>>mm;
	  if(mm<1||mm>12)
	     {
	      cout<<"\nPlease enter month from 1 to 12";
	      cout<<"\nPress any key to continue...........";
	      bioskey(0);
	      goto a;
	     }
	  b:clrscr();
	  cout<<"\n\n\nEnter the year ? ";
	  cin>>yy;
	  if(yy<1)
	     {
	      cout<<"\nPlease enter year from 1 to 32767";
	      cout<<"\nPress any key to continue........";
	      bioskey(0);
	      goto b;
	     }
	  in:clrscr();
	  cout<<"\n\n\n                     Calendar for ";
	  cout<<month[mm-1];
	  cout<<","<<yy;
	  cout<<"\n\n\n\tSun\tMon\tTue\tWed\tThu\tFri\tSat\n";
	  cout<<"\t===\t===\t===\t===\t===\t===\t===\n";
	  day(1,mm,yy);
	  for(int j=0;j<day(1,mm,yy);j++)cout<<"\t";
	  int n_days_month=m_array[mm-1];
	  if(mm==2)
	     {
	      if(yy%100==0){if((yy/100)%4==0)n_days_month++;}
	      else if(yy%4==0)++n_days_month;
	     }
	  for(int i=1;i<=n_days_month;i++)
	  {
	   if(wherex()>56)cout<<"\n";
	   cout<<"\t";
	   cout<<i;
	  }
	  cout<<"\n\n  Press any key to continue...........";
	  cout<<"\n Or Arrow keys to see more..............";
	  cout<<"\n Press Escape to exit.............";
	  ot:switch(bioskey(0))
	  {
	      case 19712://....to see the right screen
			 if(mm+1>12)goto ot;
			 else mm++;
			 goto in;
	      case 19200://....to see the left screen
			 if(mm-1<1)goto ot;
			 else mm--;
			 goto in;
	      case 18432://....to see the up screen
			 yy--;
			 goto in;
	      case 20480://....to see the down screen
			 yy++;
			 goto in;
	      case 283  :goto start;      //.....escape
	      default:   goto ot;
	  }
  case 818:break;
  default:cout<<"\n\n\n         Please enter a choice from 1 to 2";
	  cout<<"\n         Press any key to continue.......";
	  bioskey(0);
	  goto start;
 }
}
int day(long int dd1,long int mm1,long int yy1)
{
 int m_array[12]={31,28,31,30,31,30,31,31,30,31,30,31};
 long int tot=0;
 tot += (yy1-1)*365+(yy1-1)/4-(yy1-1)/100+(yy1-1)/400;
 if(mm1!=1)
 {
   for(int i=1;i<=mm1-1;i++)  tot += m_array[i-1];
 }
 if(mm1>2)
   {
       if(yy1%100==0)if(yy1%4==0)tot++;
       else if(yy1%4==0)tot++;
   }
 tot+=dd1;
 return(tot%7);
}