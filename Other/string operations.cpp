#include<iostream.h>
#include<conio.h>
#include<stdio.h>
void main()
{
 clrscr();
 char text[100],text_rev[100];
 int i,c,w=1,j,l=0,n=0,u;
 cout<<"Enter the string ?\n";
 gets(text);
 fflush(stdin);
 clrscr();
 cout<<"\n\n...............MESSAGES..........";
 while(text[l]!='\0')l++;       //.....Calculate length of string
 c=l;
 cout<<"\n\n1) Length of the string = "<<l; getch();
 cout<<"\n\n2) Words are :-\n   ";
 for(i=0;i<=l-1;i++)
    {
     if (text[i] == ' ')
	{
	  cout<<"\n   ";
	  c -= 1;
	  w +=1;
	  continue;
	}
     cout<<text[i];
    }
 getch();
 for(i=0;i<=l-1;i++)            //.....Loop to convert string in
    {                                       //.... uppercase
     if((text[i]>='a')&&(text[i]<='z'))
     text[i] -= 32;
    }
 cout<<"\n\n3) String in upper case :-\n   ";
 cout<< text;
 for(i=l-1;i>=0;i--)                        //.....Loop to put reverse
    {                                       //.....string in text_rev
     text_rev[n] = text[i];
     n++;
    }
 getch();
 cout<<"\n\n4) Reverse string :-\n   ";     //....Print reverse string
 for (i=0;i<=l-1;i++) cout<<text_rev[i];          getch();
 cout<<"\n\n5) Number of characters are = "<<c;   getch();
 cout<<"\n\n6) Number of words are = "<<w<<"\n\n";     getch();
 int f=0;
 for(i=0;i<l;i++)if(text[i]!=text_rev[i])  f=5;
 if(f==5)cout<<"7) String is not a palindrome.\n\n";
 else
      cout<<"7) String is a palindrome.\n\n";
 getch();
 int cou = 0;
 for(j=0;text[j]!='\0';j++)
 if((text[j]=='a')||(text[j]=='e')||(text[j]=='i')
     ||(text[j]=='o')||(text[j]=='u')||(text[j]=='A')
     ||(text[j]=='E')||(text[j]=='I')||(text[j]=='O')
     ||(text[j]=='U')) cou= cou+1;
 cout<<"8) Number of vowels in string = "<<cou;
 cout<<"\n\n\nPress any key to continue.......";
 getch();
 clrscr();
 int line=0,app;
 char ch = 'A'-1;
 for (j=1;j<=26;j++)
     {
	ch++;
	app = 0;

	for (i=0;i<l;i++)                   //.....To find no. of appearance
	    {  if(text[i]==ch) ++app;  }    //.....of letter 'ch' in string

	if (app!=0)   //.....if string contain 'ch'
	  {
	    ++line;
	    cout<<text<<"\n";
	    for (i=0;i<l;i++)
		{
		  if(text[i]==ch) cout<<"-";
		  else cout<<" ";
		}
	    cout<<"    "<<ch<<" appears "<<app<<" times.\n";
	    if((line==12)||(line==24)) getch();
	  }
     }
 getch();
}