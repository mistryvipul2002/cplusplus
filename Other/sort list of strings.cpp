#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
int strcompare(char s1[100],char s2[100]);
void main()
{
 clrscr();
 char name[100][100],sm_stri[100],temp[100];
 int n,pos;
 cout<<"Enter the number of strings =====> ";
 cin>>n;
 cout<<"\n\nStart entering strings.........\n\n";
 for(int i=0;i<n;i++)
 {
  cout<<"("<<i+1<<") ";
  gets(name[i]);
  cout<<"\n";
 }
 for(i=0;i<n;i++)
 {
  strcpy(sm_stri , name[i]);
  pos =i;
  for(int j=(i+1);j<n;j++)
      if(strcompare(name[j],sm_stri)<0){  strcpy(sm_stri , name[j]);pos =j; }
  strcpy( temp , name[i]);
  strcpy( name[i] , sm_stri);
  strcpy( name[pos] , temp);
 }
 clrscr();
 cout<<"               SORTED LIST                     \n";
 cout<<"               =========== \n";
 for(i=0;i<n;i++)
 {
  cout<<"("<<i+1<<") ";
  puts(name[i]);
  cout<<"\n";
 }
 getch();
}
int strcompare(char s1[100],char s2[100])
{
 int l1 = strlen(s1);
 int l2 = strlen(s2);
 int le=0;
a: if((le<l1)||(le<l2))
 {
  if(s1[le]<s2[le]) return(-1);
  else
      {
       if(s1[le]>s2[le]) return(1);
       else { le++; goto a;}
      }
 }
 return(0);
}