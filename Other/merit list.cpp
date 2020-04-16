#include<iostream.h>
#include<conio.h>
main()
{
 clrscr();
 int marks[100][50],stud,subj,i,j,k=0,l,total=0,per;

 //...........Entering marks..................
 cout<<"Enter the number of student ? ";
 cin>>stud;
 cout<<"Enter the number of subjects ? ";
 cin>>subj;
 for(i=0;i<stud;i++)
    {
     clrscr();
     cout<<"Enter marks of roll no. = "<<i+1<<"\n";
     for(j=0;j<subj;j++)
	{
	 cout<<"Subject "<<j+1<<"=";
	 cin>>marks[i][j];
	}
    }

 //...........Report card..........
 for(i=0;i<stud;i++)
    {
     clrscr();
     cout<<"\n              REPORT CARD               ";
     cout<<"\n              ROLL NO ="<<i+1<<"\n\n";
     cout<<"SUBJECT          MARKS          OUT OF\n";
     cout<<"=======          =====          ======\n";
     for(j=0;j<subj;j++)
	{
	 cout<<"SUBJECT "<<j+1<<"        "<<marks[i][j]<<"\t\t100";
	 cout<<"\n";
	 total += marks[i][j];
	 if (marks[i][j] > k)  { k=marks[i][j];  l=j+1; }
	}
     cout<<"--------------------------------------\n";
     cout<<"Total            "<<total<<"\t\t"<<100*subj;
     per = total/subj;
     cout<<"\nPercentage = "<<per<<"%\n";
     cout<<"Grade = ";
     if(per>=60) cout<<"A\n";
     else  {
	    if (per>=48)cout<<"B\n";
	    else {
		  if (per>=36)  cout<<"C\n";
		  else cout<<"D\n";
		 }
	   }
     cout<<"Result = ";
     if  (per<36) cout<<"Fail.\n";
     else cout<<"Pass.\n";
     cout<<"Highest marks in\n";
     cout<<"Subject "<<l<<"         "<<k<<"\t\t100";
     k=0;
     total=0;
     if (i!=(stud-1))
     {
     cout<<"\n\nPress any key to continue..........";
     getch();
     clrscr();
     }
     else {cout<<"\n\nEnd.......";getch();}
    }
 clrscr();

 //..............Merit list..............
 cout<<".................... M E R I T   L I S T ................\n\n";
 int m,p=0,pos;
 for(i=0;i<stud;i++)
    {
     for(m=0;m<stud;m++)
	{
	 for(j=0;j<subj;j++)  total += marks[m][j];
	 if (total>p)   { p = total;pos = m;}
	 total =  0;
	}
     cout<<"Rank "<<i+1<<" = Roll No. "<<(pos+1)<<"\tPercent = "<<p/subj<<" %\n";
     p=0;
     for (j=0;j<subj;j++) marks[pos][j] = 0;
    }
 getch();
}




