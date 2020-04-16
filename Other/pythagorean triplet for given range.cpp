#include<iostream.h>
#include<conio.h>
void main()
{
 clrscr();
 int a,b,c,d,e;
 cout<<"Enter the range for pythagorean triplets......";
 cout<<"\nStart from......\n";
 cin>>e;
 cout<<"End at.....\n";
 cin>>d;
 clrscr();
 cout<<"Pythagorean triplets are.....\n";
 for(a=e;a<=d;a++)
    {
     for(b=a;b<=d;b++)
	{
	 for(c=b;c<=d;c++)
	    {
	     if(c*c==b*b+a*a)cout<<a<<"\t"<<b<<"\t"<<c<<"\n";
	    }
	}
    }
 getch();
}



