#include<iostream.h>
#include<conio.h>
main()
{
 //...THIS IS A PROGRAMME TO GENERATE PRIME NUMBERS OF GIVEN RANGE
 clrscr();
 float i,a; int d;
 cout<<"Enter the range of numbers ?\nI will tell you prime numbers upto that range.";
 cin>>d;
 cout<<"\n1\t"<<"2\t";
 for (i=3;i<=d;i++)
    {
     for(a=2;a<=(i-1);a++)
	{
	 if (a==(i-1)) goto back;
	 else
	    { if(i/a == int(i/a)) goto vpl; }
	}
    back:cout<<i<<"\t";
    vpl:;
   }
 getch();
}