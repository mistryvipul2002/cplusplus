//............C L A S S    M A N A G E M E N T     S Y S T E M........
//............==================================================........
//............DEVELOPED BY ======> "VIPUL	 MISTRY"................
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#define N_SIZE 21
char subjects[9][20] ={	"Maths","Biology",
			"Computer","Hindi","Economics","Physical Education",
			"English","Physics","Chemistry",};
class student
{ 	char name[N_SIZE];
	char father_name[N_SIZE];
	char mother_name[N_SIZE];
	char remarks[80];
	int subject_code[5];
	int marks1[5];
	int marks2[5];
	int marks3[5];
	int registeration_num;
 public:void getdata();
	void mod_marks();
	void display();
	void merit();
	int get_rank();
	float calc_tot_percent();
};
void student::getdata()
{ clrscr();
  //.....enter data
  cout<<"\n";
  cout<<"       ษออออออออออออออออออออออออออออออออออออออออออออออออออออออป  \n";
  cout<<"       บ        D A T A     E N T E R I N G     M E N U       บ  \n";
  cout<<"       ศออออออออออออออออออออออออออออออออออออออออออออออออออออออผ  \n\n";
  cout<<"        a)  Enter your Name (max "<<N_SIZE-1<<" char) ?   ";gets(name);
  cout<<"        b)  Enter Father Name (max "<<N_SIZE-1<<" char) ? ";gets(father_name);
  cout<<"        c)  Enter Mother Name (max "<<N_SIZE-1<<" char) ? ";gets(mother_name);
  cout<<"        d)  Your Subjects :-\n";
  cout<<"            1) English\n";
  cout<<"            2) Physics\n";
  cout<<"            3) Chemistry\n";
  cout<<"            4) Maths-0 or Biology-1\n";
  cout<<"               Enter your choice (0/1)? ";cin>>subject_code[0];
  cout<<"            5) Computer-2 or Hindi-3 or Economics-4 or Physical Education-5\n";
  cout<<"               Enter your choice (2/3/4/5) ? ";cin>>subject_code[1];
  subject_code[2]=6;subject_code[3]=7;subject_code[4]=8;
  cout<<"        e)  Enter Registration Number ? ";cin>>registeration_num;
  cout<<"        f)  Remarks (max 80 char)....\n";
  gets(remarks);
  //....enter marks
  clrscr();
  cout<<"       ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออป \n";
  cout<<"       บ      M A R K S       E N T E R I N G     M E N U      บ \n";
  cout<<"       ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออผ \n";
  cout<<"       Enter marks for 1st Pre Board ? \n";
  for(int i=0;i<5;i++)
  {	cout<<"        "<<i+1<<") "<<subjects[subject_code[i]]<<"\t\t";
	cin>>marks1[i];}
  clrscr();
  cout<<"       ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออป \n";
  cout<<"       บ      M A R K S       E N T E R I N G     M E N U      บ \n";
  cout<<"       ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออผ \n";
  cout<<"       Enter marks for  2nd Pre Board ? \n";
  for(i=0;i<5;i++)
  {	cout<<"        "<<i+1<<") "<<subjects[subject_code[i]]<<"\t\t";
	cin>>marks2[i];}
  clrscr();
  cout<<"       ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออป \n";
  cout<<"       บ      M A R K S       E N T E R I N G     M E N U      บ \n";
  cout<<"       ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออผ \n";
  cout<<"       Enter marks for  Main Board ? \n";
  for(i=0;i<5;i++)
  {	cout<<"        "<<i+1<<") "<<subjects[subject_code[i]]<<"\t\t";
	cin>>marks3[i];}
  //....write to file
  fstream outfile;
  outfile.open("student.dat",ios::app|ios::binary); //...open the file student.dat
  outfile.write((char*)this,sizeof(student)); //..write object in file
  outfile.flush();outfile.close();
}
void student::merit()
{ clrscr();
  cout<<"       ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออป \n";
  cout<<"       บ            M  E  R  I  T        L  I  S  T            บ \n";
  cout<<"       ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออผ \n\n";
  cout<<"       Name             Reg.No.       Rank      Percent\n";
  cout<<"       ====             =======       ====      =======\n";
  fstream infile;infile.open("student.dat",ios::in|ios::binary);
  if(infile.fail()){cout<<"\nFile read error or file does not exist";getch();return;}
  infile.seekg(0,ios::end);
  int offset=infile.tellg();//-sizeof(student);
  int i=7;
  for(int t=0;t<(offset/sizeof(student));t++)
  { infile.seekg(0);
    while(infile.tellg()!=offset)//....while end of file is not reached
    { infile.read((char*)this,sizeof(student));
      if(get_rank()==t+1)
      {  gotoxy(8,i);cout<<name;
	 gotoxy(25,i);cout<<registeration_num;
	 gotoxy(39,i);cout<<get_rank();
	 gotoxy(49,i);cout<<calc_tot_percent();
	 i++;
      }
    }
  }
  infile.close();
  getch();
}
void student::mod_marks()
{ clrscr();
  cout<<"       ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออป \n";
  cout<<"       บ        M O D I F Y       M A R K S       M E N U      บ \n";
  cout<<"       ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออผ \n\n";
  cout<<"       Enter registration number of student ? ";
  int reg;cin>>reg;

  fstream infile;infile.open("student.dat",ios::in|ios::binary);
  if(infile.fail()){cout<<"\nFile read error or file does not exist";getch();return;}
  infile.seekg(0);int found_flag=0,offset=0;
  while(infile.eof()==0)       //....while end of file is not reached
     {  infile.read((char*)this,sizeof(student));  //...read record
	if(registeration_num==reg)    //....if match
	   { offset=infile.tellg()-sizeof(student);   //...file position of record found
	     found_flag=1;break;
	   }
     }
  infile.close();
  if(found_flag==0){    cout<<"\n\nRecord not found.....";
			getch();return;}
  //.............modify marks
  cout<<"       1st Pre Board-1\n       2nd Pre Board-2\n       Main Board-3\n";
  cout<<"       Modify marks for Board (1/2/3) ? ";
  int cho;cin>>cho;
  cout<<"       Enter marks ? \n";
  for(int i=0;i<5;i++)
  {	cout<<"        "<<i+1<<") "<<subjects[subject_code[i]]<<"\t\t";
	switch(cho)
	{ case 1 :cin>>marks1[i];break;
	  case 2 :cin>>marks2[i];break;
	  case 3 :cin>>marks3[i];
	}
  }
  infile.open("student.dat",ios::out|ios::in|ios::binary);
  infile.seekp(offset,ios::beg);
  infile.write((char*)this,sizeof(student));
  infile.close();
}
int student::get_rank()
{ fstream file;student stud2;
  file.open("student.dat",ios::in|ios::out|ios::binary);
  if(file.fail()){cout<<"\nFile read error or file does not exist";
		  getch();return(0);}
  int rank=1;
  file.seekg(0,ios::end);
  int offset=file.tellg();//-sizeof(student);
  file.seekg(0);
  while(file.tellg()!=offset)       //....while end of file is not reached
  { file.read((char*)(&stud2),sizeof(student));
    if(stud2.calc_tot_percent()>calc_tot_percent())rank++;
  }
  file.close();
  return(rank);
}
float student::calc_tot_percent()
{ float tot_marks=0;
  for(int i=0;i<5;i++) tot_marks+=marks1[i]+marks2[i]+marks3[i];
  return(tot_marks/15);
}
void student::display()
{ clrscr();
  cout<<"Enter the registration number ?  ";int reg;cin>>reg;
  //...search for the record......
  fstream infile;infile.open("student.dat",ios::in|ios::binary);
  if(infile.fail()){cout<<"\nFile read error or file does not exist";getch();return;}
  infile.seekg(0);int found_flag=0,offset=0;
  while(infile.eof()==0)       //....while end of file is not reached
     {  infile.read((char*)this,sizeof(student));  //...read record
	if(registeration_num==reg)    //....if match
	    {found_flag=1;break;}
     }
  infile.close();
  if(found_flag==0){cout<<"\n\nRecord not found.....";getch();return;}
  clrscr();
  cout<<"       ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออป \n";
  cout<<"       บ     P R O G R E S S      R E P O R T      C A R D     บ \n";
  cout<<"       ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออผ \n\n";
  cout<<"       Name :-        "<<name;
  cout<<"\n       Father Name :- "<<father_name;
  cout<<"\n       Mother name :- "<<mother_name;
  cout<<"\n       Registration Number :- "<<registeration_num;
cout<<"\n\n       Subjects            1st PreBoard   2nd PreBoard   MainBoard";
  cout<<"\n       ========            ============   ============   =========";
  for(int i=0;i<5;i++){
	  cout<<"\n       "<<subjects[subject_code[i]];
	  gotoxy(31,12+i);cout<<marks1[i];
	  gotoxy(47,12+i);cout<<marks2[i];
	  gotoxy(60,12+i);cout<<marks3[i];
  }
  cout<<"\n       -----------------------------------------------------------";
  cout<<"\n       Total";
  int tot[3]={0,0,0};
  gotoxy(31,18);
  for(i=0;i<5;i++)tot[0]+=marks1[i];cout<<tot[0];
  gotoxy(47,18);
  for(i=0;i<5;i++)tot[1]+=marks2[i];cout<<tot[1];
  gotoxy(60,18);
  for(i=0;i<5;i++)tot[2]+=marks3[i];cout<<tot[2];
  cout<<"\n       Percentage";
  gotoxy(31,19);cout<<tot[0]/5<<"%";
  gotoxy(47,19);cout<<tot[1]/5<<"%";
  gotoxy(60,19);cout<<tot[2]/5<<"%";
  cout<<"\n       Overall Percentage :- "<<calc_tot_percent()<<"%";
  cout<<"\tResult :- ";
  if(calc_tot_percent()>=40)cout<<"PASS";
  else cout<<"FAIL";
  cout<<"\n       Rank :- "<<get_rank();
cout<<"\n\n       Remarks :- ";puts(remarks);
  getch();
}
void main()
{
 student stud;
start: clrscr();
 cout<<"\n\n\n\n\n";
 cout<<"          ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออป  \n";
 cout<<"          บ    C L A S S   M A N A G E M E N T   S Y S T E M      บ  \n";
 cout<<"          ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออน  \n";
 cout<<"          บ                                                       บ  \n";
 cout<<"          บ      1) Add student record                            บ  \n";
 cout<<"	  บ      2) Modify student marks                          บ  \n";
 cout<<"	  บ      3) Display a student record                      บ  \n";
 cout<<"	  บ      4) Display Merit List                            บ  \n";
 cout<<"	  บ      5) Exit                                          บ  \n";
 cout<<"	  บ                                                       บ  \n";
 cout<<"	  บ  Enter your choice ?  _                               บ  \n";
 cout<<"	  บ                                                       บ  \n";
 cout<<"	  ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออผ  \n";
 gotoxy(35,16);
 int choice;
 cin>>choice;
 switch(choice)
    {
     case 1: stud.getdata();       //  call member function getdata()
	     goto start;
     case 2: stud.mod_marks();     //  call member function get_marks()
	     goto start;
     case 3: stud.display();
	     goto start;
     case 4: stud.merit();
	     goto start;
     case 5: break;
     default: cout<<"\n\n\n             Wrong choice.\n\n";
	      cout<<"             Press any key to continue......";
	      getch();
	      goto start;
    }
}
