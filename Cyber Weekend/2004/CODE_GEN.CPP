#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<fstream.h>
void main(){
	ofstream outfile;
	ifstream infile;
	infile.open("code.in");
	outfile.open("code.out");

	char s[80];

  while(!infile.eof()){
	//......read the line from file
	infile.getline(s,80);

	char next=' ';		//.....' ' means empty and 'p' means not empty
	char reg=' ';
	char buffer=' ';

	int n=0;	//....storage
	int cou=0;
	while(next!='\0'){
		next=s[cou++];
		if((next>='A'&&next<='Z')||(next>='a'&& next<='z')){	//....it is a operand
			if(buffer==' '){
				buffer=next;
			}
			else if(reg==' '){
				reg='p';
				outfile<<"L "<<buffer<<"\n";
				buffer=next;
			}
			else{
				outfile<<"ST $"<<++n<<"\n";	//....put register in storage
				outfile<<"L "<<buffer<<"\n";	//....load buffer in reg
				buffer=next;
			}
		}
		//..........if next is operator
		else if(next=='+'){
			if(buffer==' '){	    //....buffer empty
				//....we have to multiply storage element
				outfile<<"A $"<<n<<"\n";
				n--;		//...reduce storage by 1
			}
			else{
				outfile<<"A "<<buffer<<"\n";	//....add buffer to reg
				buffer=' ';	//...clear buffer
			}
		}
		else if(next=='*'){
			if(buffer==' '){	    //....buffer empty
				//....we have to multiply storage element
				outfile<<"M $"<<n<<"\n";
				n--;		//...reduce storage by 1
			}
			else{
				outfile<<"M "<<buffer<<"\n";	//....multiply buffer to reg
				buffer=' ';	//...clear buffer
			}
		}
		else if(next=='-'){
			if(buffer==' '){	    //....buffer empty
				//....we have to subtract reg from storage element
				outfile<<"N"<<"\n";	//....first negate the register
				outfile<<"A $"<<n<<"\n";	//...then add storage element
				n--;		//...reduce storage by 1
			}
			else{
				outfile<<"S "<<buffer<<"\n";	//....subtract buffer to reg
				buffer=' ';	//...clear buffer
			}
		}
		else if(next=='/'){
			if(buffer==' '){	    //....buffer empty
				//....we have to divide storage element by reg
				//....i.e. to swap contents of reg and storage
				outfile<<"ST $"<<++n<<"\n";		//....put register in storage
				outfile<<"L $"<<n-1<<"\n";	//....load earlier storage in reg
				outfile<<"D $"<<n<<"\n";	//....now do the division
				n-=2;	//...remove the two storage locations
			}
			else{
				outfile<<"D "<<buffer<<"\n";	//....divide buffer to reg
				buffer=' ';	//...clear buffer
			}
		}
		else if(next=='@'){	//.......negation sign @(unary operator)
			if(buffer==' '){	    //....buffer empty
				//....we have to NEGATE reg ONLY
				outfile<<"N"<<"\n";	//....first negate the register
			}
			else{
				if(reg==' '){
					outfile<<"L "<<buffer<<"\n";	//....load buffer in reg
					outfile<<"N"<<"\n";	//....now do the negation
					reg='p';
					buffer=' ';	//...clear buffer
				}
				else{
					outfile<<"ST $"<<++n<<"\n";		//....put register in storage
					outfile<<"L "<<buffer<<"\n";	//....load buffer in reg
					outfile<<"N"<<"\n";	//....now do the negation
					buffer=' ';	//...clear buffer
				}
			}
		}
	}
	outfile<<"\n";
  }

	infile.close();
	outfile.close();
}