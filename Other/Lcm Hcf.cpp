#include<iostream.h>
#include<conio.h>
void main()
{
 clrscr();
 //............FIND LCM AND HCF...............
 int a,b,hcf,lcm=1,n=1;
 cout<<"Enter two numbers ?\n";
 cin>>a>>b;
 back:if((lcm%a==0)&&(lcm%b==0))
 cout<<"LCM = "<<lcm<<"\nHCF = "<<a*b/lcm;
 else { lcm++;goto back;}
 getch();
}