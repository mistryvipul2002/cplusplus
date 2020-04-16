#include<dos.h>
#include<process.h>
#include<stdio.h>
#include<conio.h>
int y=2001;

//this defines a structure for date
struct da_te
{int dd;
 int mm;
 int yy;
}date;


// this function gives the number of days in a year
int year(int yy)
{	if(yy%100==0)
		{if(yy%400==0)
		 return 366;
		 else
		 return 365;
		}
	else
		{if(yy%4==0)
		 return 366;
		 else
		 return 365;
		}
}

//this function gives the no days in a month
int month(int mm,int yy)
{	 int day;
	 switch(mm)
		{case 1: day=31;
			 break;
		 case 2: if(year(yy)==366)
			 day=29;
			 else
			 day=28;
			 break;
		 case 3: day=31;
			 break;
		 case 4: day=30;
			 break;
		 case 5: day=31;
			 break;
		 case 6: day=30;
			 break;
		 case 7: day=31;
			 break;
		 case 8: day=31;
			 break;
		 case 9: day=30;
			 break;
		 case 10:day=31;
			 break;
		 case 11:day=30;
			 break;
		 case 12:day=31;
			 break;
		}
	 return day;
}

//this function returns day for dates onwards 1 1 2001
void put_day1(int da)
	{gotoxy(30,12);
	 printf("\n\t\t Day for %d/%d/%d: ",date.dd,date.mm,date.yy);
	 switch(da)
	{case 0:printf("monday");
		break;
	 case 1:printf("tuesday");
		break;
	 case 2:printf("wednesday");
		break;
	 case 3:printf("thursday");
		break;
	 case 4:printf("friday");
		break;
	 case 5:printf("saturday");
		break;
	 case 6:printf("sunday");
		break;
	 default: printf("unday");
	}
}

//this function gives day for dates before 1 1 2001
void put_day2(int da)
{        gotoxy(30,12);
	 printf("\n\t\t Day for %d/%d/%d: ",date.dd,date.mm,date.yy);
	 switch(da)
		{case 0:printf("monday");
			break;
		 case 1:printf("sunday");
			break;
		 case 2:printf("saturday");
			break;
		 case 3:printf("friday");
			break;
		 case 4:printf("thrusday");
			break;
		 case 5:printf("wednesday");
			break;
		 case 6:printf("tuesday");
			break;
		 default: printf("unday");
		}
}

//this function checks the validity of data
int check(int dd,int mm,int yy)
{clrscr();
 gotoxy(10,7);
 if((yy<1||yy>9999)||(mm<1||mm>12)||(mm==2&&dd>29)||(mm==2&&year(yy)==365&&dd==29)||(dd<1||dd>31))
	{if(yy<1||yy>9999)
		printf("\n\t\t* Enter date between 1/1/0001 and 31/12/9999\n");
	 if(mm<1||mm>12)
		printf("\n\t\t* Month should be between 01 and 12\n");
	 if(mm==2&&dd>29)
		printf("\n\t\t* February cannot have more than 29 days\n");
	 if(mm==2&&year(yy)==365&&dd==29)
		{printf("\n\t* Since %d is not a leap year so february",yy);
		 printf(" cannot have 29 days!!");
		}
	 if(dd<1||dd>31)
		printf("\n\t\t* Day should be between 01 and 31");
	 gotoxy(15,5);
	 printf("***************ERROR IN ENTERING DATA**************");
	 return 0;
	}
	else return 1;
}


void life3(void)
{
int i,da;
int y=2001;
long int day;
		if((date.yy>=y)&&(check(date.dd,date.mm,date.yy)))
		{day=0;
		 da=0;
		 for(i=2001;i<date.yy;i++)
		 day=day+year(i);
		 for(i=1;i<date.mm;i++)
		 day=day+month(i,date.yy);
		 day=day+date.dd;
		 da=(day-1)%7;
		 put_day1(da);
		}
		if((date.yy<y)&&(check(date.dd,date.mm,date.yy)))
		{day=0;
		 da=0;
		 for(i=date.yy;i<y;i++)
			day=day+year(i);
		 for(i=1;i<date.mm;i++)
			day=day-month(i,date.yy);
		 day=day-date.dd;
		 da=(day+1)%7;
		 put_day2(da);
		}
}



void life2(void)
{int i,j,x,z,da;
 int y=2001;
 long int day;
 void print(void);
 date.dd=1;
 z=10;
 clrscr();
 gotoxy(13,3);
 printf("****************MILLENIUM CALENDER***************");
 printf("\n\n\t\t   CALENDER FOR(MONTH YEAR):%d %d",date.mm,date.yy);
	if((date.yy>=y)&&(check(date.dd,date.mm,date.yy)))
	{printf("\n");
	 print();
			 day=0;
			 da=0;
			 for(i=2001;i<date.yy;i++)
			 day=day+year(i);
			 for(i=1;i<date.mm;i++)
			 day=day+month(i,date.yy);
			 day=day+date.dd;
			 da=(day-1)%7;
				switch(da)
				{case 0 :gotoxy(21,z);
					 x=21;
					 printf("%d",date.dd);
					 break;
				 case 1 :gotoxy(29,z);
					 x=29;
					 printf("%d",date.dd);
					 break;
				 case 2 :gotoxy(37,z);
					 x=37;
					 printf("%d",date.dd);
					 break;
				 case 3 :gotoxy(45,z);
					 x=45;
					 printf("%d",date.dd);
					 break;
				 case 4 :gotoxy(53,z);
					 x=53;
					 printf("%d",date.dd);
					 break;
				 case 5 :gotoxy(61,z);
					 x=61;
					 printf("%d",date.dd);
					 break;
				 case 6 :gotoxy(13,z);
					 x=13;
					 printf("%d",date.dd);
					 break;
				}
				for(j=2;j<=month(date.mm,date.yy);j++)
				{	if(x<60)
					x+=8;
					else
					{z+=2;
					 x=13;
					}
					gotoxy(x,z);
					printf("%d",j);
				}
	 }
	if((date.yy<y)&&(check(date.dd,date.mm,date.yy)))
	{printf("\n");
	 print();
			 date.dd=1;
			 day=0;
			 da=0;
			 for(i=date.yy;i<y;i++)
			 day=day+year(i);
			 for(i=1;i<date.mm;i++)
			 day=day-month(i,date.yy);
			 day=day-date.dd;
			 da=(day+1)%7;
				switch(da)
				{case 0 :gotoxy(21,z);
					 x=21;
					 printf("%d",date.dd);
					 break;
				 case 1 :gotoxy(13,z);
					 x=13;
					 printf("%d",date.dd);
					 break;
				 case 2 :gotoxy(61,z);
					 x=61;
					 printf("%d",date.dd);
					 break;
				 case 3 :gotoxy(53,z);
					 x=53;
					 printf("%d",date.dd);
					 break;
				 case 4 :gotoxy(45,z);
					 x=45;
					 printf("%d",date.dd);
					 break;
				 case 5 :gotoxy(37,z);
					 x=37;
					 printf("%d",date.dd);
					 break;
				 case 6 :gotoxy(29,z);
					 x=29;
					 printf("%d",date.dd);
					 break;
				}
				for(j=2;j<=month(date.mm,date.yy);j++)
				{	if(x<60)
					x+=8;
					else
					{z+=2;
					 x=13;
					}
					gotoxy(x,z);
					printf("%d",j);
				}
	}
}


	void life1(void)
	{for(date.mm=1;date.mm<=12;date.mm++)
	       {life2();
		gotoxy(15,22);
		printf("    press any key to continue:");
		getch();
	       }
	}

void print()
{
clrscr();
gotoxy(13,3);
printf("****************MILLENIUM CALENDER***************");
printf("\n\n\t\t   CALENDER FOR(MONTH YEAR):%d %d",date.mm,date.yy);
gotoxy(1,7);
printf("        ÉÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍ»\n");
printf("        º  SUN  ³  MON	³  TUE  ³  WED	³  THU	³  FRI	³  SAT	 º\n");
printf("        ÇÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ¶\n");
printf("        º       ³	³	³	³	³	³	 º\n");
printf("        ÇÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ¶\n");
printf("        º       ³	³	³	³	³	³	 º\n");
printf("        ÇÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ¶\n");
printf("        º	³	³	³	³       ³	³	 º\n");
printf("        ÇÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ¶\n");
printf("        º       ³	³	³	³	³	³	 º\n");
printf("        ÇÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ¶\n");
printf("        º       ³	³	³	³	³	³	 º\n");
printf("        ÇÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ¶\n");
printf("        º       ³	³	³	³	³	³	 º\n");
printf("        ÈÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍ¼\n");
printf("\n\n\t                     ************PREPARED BY:-NEERAJ GAUTAM ");
}



void main()
{
char name[]="NEERAJ GAUTAM";
int i,ch,j,k;
char choice,xyz;
void life1(void);
void life2(void);
void life3(void);
textcolor(4);
textbackground(3);
clrscr();
gotoxy(30,7);
printf("MILLENIUM CALENDER");
gotoxy(1,10);
printf("\n\t  This Software of Millenium Calender is developed by Neeraj");
gotoxy(1,12);
printf("\n\t  Gautam . This software displays the calender of any entered");
gotoxy(1,14);
printf("\n\t  year and tells the day on a particular date");
gotoxy(50,18);
for(i=0;name[i]!='\0';i++)
{delay(500);
 printf("\a\a\a\a\a%c",name[i]);
}
delay(1000);
do
	{
	clrscr();
	gotoxy(10,10);
	printf("  ***************MILLENIUM CALENDER***************");
	gotoxy(10,11);
	printf("\n\t #1 Display the Calender of entered Year");
	gotoxy(10,12);
	printf("\n\t #2 Display the Calender of a Month of entered Year");
	gotoxy(10,13);
	printf("\n\t #3 Display the Day on entered Date");
	gotoxy(10,14);
	printf("\n\t #4 Exit");
	gotoxy(10,15);
	printf("\n\t    Enter your Choice(1/2/3/4):");
	gotoxy(35,20);
	printf("PRODUCED BY:- NEERAJ GAUTAM");
	gotoxy(40,16);
	scanf("%d",&i);
		switch(i)
		{case 1: clrscr();
			 gotoxy(30,11);
			 printf("\n\t\t Enter the Year(yyyy):");
			 scanf("%d",&date.yy);
			 life1();
			 break;
		 case 2: clrscr();
			 gotoxy(30,11);
			 printf("\n\t\t Enter the month and year(mm yyyy):");
			 scanf("%d%d",&date.mm,&date.yy);
			 life2();
			 break;
		 case 3: clrscr();
			 gotoxy(30,11);
			 printf("\n\t\t Enter the Date(dd mm yyyy):");
			 scanf("%d%d%d",&date.dd,&date.mm,&date.yy);
			 life3();
			 break;
		 case 4: exit(-1);
		}
	getch();
	scanf("%c");
	clrscr();
	gotoxy(20,13);
	printf(" Do you want to continue(y/n)?");
	scanf("%c",&xyz);
	}while(xyz=='y'||xyz=='Y');
}