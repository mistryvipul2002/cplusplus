#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
void del(char s1[100],int pos);
void upper(char c);
char str[100];
int n=0;
void main()
{
 //.............Program to print name with initials
star: clrscr();
 cout<<"Enter your full name==========> ";
 gets(str);
 char ch,ch2;
 cout<<"Enter male(m)/female(f)====> ";
 cin>>ch;
 if(ch=='f')
	      {
		cout<<"Married(m)/unmarried(u)=====> ";
		cin>>ch2;
	      }
 goto cont;
 a: cout<<"Wrong choice......";getch();goto star;
 cont:;
 if((ch!='m')&&(ch!='f'))goto a;
 if(ch=='f') if((ch2!='m')&&(ch2!='u'))goto a;

 //...........Remove extra blanks in string.............
 int i=0;
 n=0;
 while(str[0]==' ')del(str,0);  //...remove starting blank spaces of str
 while(str[i]!='\0')            //....till end of str
     {
       if(str[i]==' ')     //...whenever you get a blank
	  {
	     n=i+1;
	     while(str[n]==' ') del(str,n);   //....if another blank is found
	  }                                   //....delete it
       i++;
     }
 int l = strlen(str);               //....to remove the last blank if it is
 if(str[l-1]==' ')del(str,(l-1));   //....there

 //............Print the initials of name.............
 clrscr();
 cout<<"Name with initials.......\n\n";
 if(ch=='m')cout<<"Mr. ";
 if(ch=='f')
	      {
		if(ch2=='m')cout<<"Mrs. ";
		if(ch2=='u')cout<<"Miss ";
	      }

 //...........print remaining part of name....  � 7   �3                     
 int a=0;
 for(l=0;str[l]!='\0';l++);    //...find the length of final string
 for(i=(l-1);i>=0;i--)
    {
       if(str[i]==' ')  { a=i; break; }  //.....'a' denote the last position
    }                                      //.....of the blank in str

 if(a==0)                      //...if no blank is present
 {                             //...simply print the string as it is
    upper(str[0]);             //...making its first character uppercase
    for(i=1;i<l;i++)cout<<str[i];
 }
 else
 {
     int space[100]; //...this array stores the position of blanks in str
     n=0;
     for(i=0;i<a;i++)        //...from 1st character of str upto last blank
	 {
	   if(str[i]==' ')  { space[n]=i;  n++;  }  //...if you find blank
	 }                           //...put its position in array space[]
     upper(str[0]);  //.....make first character of str uppercase
     cout<<".";
     for(i=0;i<n;i++) { upper(str[space[i]+1]);  cout<<"."; } //..make other
	   //...characters of str after blank uppercase and print them
     upper(str[a+1]); //...make first character of lastname uppercase
     for(i=(a+2);i<l;i++) cout<<str[i];  //...print lastname
 }
 char ch3;
 cout<<"\n\n\n\n                    Want more(y/n)? ";
 cin>>ch3;
 if((ch3=='y')||(ch3=='Y'))goto star;
}
//...................Function to convert a char 'c' into uppercase
void upper(char c)
{
 if((c>='a')&&(c<='z'))c-=32;
 cout<<c;
}
//.........Function to delete char in string s1 at position pos
void del(char s1[100],int pos)
{
 int k=strlen(s1),p=0;
 for(int i=0;i<=k;i++)   //....till end of string s1
    {
       if (i!=pos)             //...if i is not the position of char to be
	     {                //...deleted put char of s1 to str
	       str[p]=s1[i];
	       p++;
	     }
    }
}U  f 
       Body text                 ��3   � � e       �-��   ��
�� �(#�&                                            �   �         AB_JAIN CPPN ARMADO  CPP�ATT     BGI>�CAL     TXT  CGA     BGI>�DIGIT   CPP�DIGIT   OBJ DSC