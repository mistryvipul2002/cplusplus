//....................my own program..........
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
void main()
{
 clrscr();
 int arr[100];int j=0,l;

 //......To enter the numbers.......
 fflush(stdin);
 fflush(stdout);
 cout<<"Enter the range to find consecutive numbers ? ";cin>>j;
 cout<<"Enter numbers\n";
 for(int i=0;i<j;i++)cin>>arr[i];

 //......To remove duplicates and replace them by -10........
 for(i=0;i<j;i++)for(l=i+1;l<j;l++)if(arr[i]==arr[l])arr[l]=-10;

 //......To print consecutive numbers......
 cout<<"\n\nConsecutive numbers are :- \n";
 for(i=0;i<j;i++)
 {
  for(l=i;l<j;l++)
  {
   if((arr[i]==arr[l]+1)||(arr[l]==arr[i]+1))cout<<arr[i]<<"  "
   <<arr[l]<<"\n";
  }
 }
 getch();
}