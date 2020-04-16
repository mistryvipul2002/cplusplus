#include<iostream.h>
#include<conio.h>
int main()
{
 clrscr();
 long int dd,mm,yy,tot;
 char month[13][10]={"January","February","March","April","May","June",
		  "July","August","September","October","November",
		  "December"};
 char week[8][10]={"Sunday","Monday","Tuesday","Wednesday",
		 "Thursday","Friday","Saturday"};
 int days[]={31,28,31,30,31,30,31,31,30,31,30,31};

 //.........Enter the date.....
 cout<<"Enter day ===> ";cin>>dd;
 cout<<"Enter month ===> ";cin>>mm;
 cout<<"Enter year ===> ";cin>>yy;

 //......Check the validity of the given date.....
 if((yy%4==0)&&(mm==2)&&(dd==29)) goto b;
 else
      if((dd<1)||(dd>days[mm-1])||(yy<1)||(mm<1)||(mm>12)) goto end;
      else
	  {
	   //...........To print the date with appropriate suffix.....
	   b:
	   clrscr();
	   cout<<"\n\n\n\n\n\n\n    THE DATE YOU HAVE ENTERED IS ===>  ";
	   cout<<dd;
	   if((dd>10)&&(dd<14)) cout<<"th ";
	   else  {
		  switch(dd%10)
			{
			 case 1:cout<<"st ";break;
			 case 2:cout<<"nd ";break;
			 case 3:cout<<"rd ";break;
			 default:cout<<"th ";
			}
		 }
	   cout<<month[mm-1];
	   cout<<" "<<yy<<" ";

	   //........To find the day of the given date....
	   tot = (yy-1)*365 + (yy-1)/4 + (yy-1)/400 - (yy-1)/100;
	   if((yy%4==0)&&(mm>2))tot+=1;
	   for(int i=0;i<(mm-1);i++)tot+=days[i];
	   tot +=dd;
	   cout<<week[tot%7]<<".";

	   //...........Terminate the program.............
	   goto a;
	  }

 //..................
 end:cout<<"Invalid date.";
 a:getch();
 return 0;
}