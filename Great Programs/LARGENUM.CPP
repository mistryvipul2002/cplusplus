#include<process.h>
#include<string.h>
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#define MAXRANGE 200
class lanum{
		char *num;
	public:
		int len;
		lanum(){num=NULL;}
		//.......following is the most important function of program
		//...all function calls when take arg.s invoke this function
		//...and all arg.s make a copy of passed objects due to this function
		//...only otherwise passed objects would have been copied to fuction
		//...arg.s bitwise that is exactly the same and hence their num fields
		//...would also be common and when function is over and the objects
		//...in arguments are destroyed then the num of this object and
		//...hence num of original object which was passed is also deleted
		//...when "lanum c=a;" is given then also this function is called and
		//...this is what actually happens when object is passed to a function
		//...when "lanum c(a);" is given then also this function is called
		lanum(lanum &temp){
			num=new char[temp.len];
			len=temp.len;
			for(int i=0;i<len;i++)
				num[i]=temp.num[i];
		}
		void display(){
			if(num[0]!='+')cout<<num[0];
			for(int i=1;i<len;i++)
			cout<<num[len-i];
		}
		void getnum(){
			char *temp=new char[MAXRANGE];
			if(temp==NULL){
				cout<<"Not enough memory";
				exit(0);
			}
			gets(temp);

			int cond=(temp[0]=='-'||temp[0]=='+');
			if(cond)len=strlen(temp);
			else len=strlen(temp)+1;
			num = new char[len];
			if(num==NULL){
				cout<<"Not enough memory";
				exit(0);
			}

			num[0]=(temp[0]=='-'?'-':'+');
			//....reverse the number
			for(int i=1;i<len;i++)
				num[i]=temp[cond?len-i:len-1-i];

			delete(temp);
		}
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//.......the following function is not correct
		void complement(){
			for(int i=1;i<len;i++) num[i]=(9-(num[i]-48))+48;
			num[0]='+';

			lanum nw;
			nw.num=new char[2];
			if(nw.num==NULL){
				cout<<"Not enough memory";
				exit(0);
			}
			nw.len=2;
			nw.num[0]='+';
			nw.num[1]='1';

			*this= (*this)+nw;  //....add 1 to current number

			num[0]='-';  //...sign restored
		}
		void normalise(){
			if(num[0]=='+'){
				for(int i=len-1;i>=2;i--)
					if(num[i]!='0')break;
					else {len=i;}
			}
			if(num[0]=='-'){
				int counter=0;  //....tells no. of 9's at end
				for(int i=len-1;i>0;i--){
					if(num[i]!='9')break;
					else counter++;
				}

				if(counter==2)return;
				int size=len-counter+2;   //.....size which should be

				char *nw=new char[size];
				if(nw==NULL){
					cout<<"Not enough memory";
					exit(0);
				}
				for(i=0;i<size-2;i++)	nw[i]=num[i];
				nw[size-2]=nw[size-1]='9';
				delete(num);
				num=nw;
				len=size;
			}
		}
		lanum operator=(lanum obj){
			delete(num);
			len=obj.len;
			num=new char[len];
			for(int i=0;i<len;i++)num[i]=obj.num[i];
			return(*this);
		}
		friend lanum operator*(lanum,lanum);
		friend int operator>(lanum,lanum);
		friend int operator==(lanum,lanum);
		friend int operator<(lanum,lanum);
		friend lanum operator+(lanum,lanum);
		friend lanum operator-(lanum,lanum);
		~lanum(){
			delete(num);
		}
};
int operator>(lanum num1,lanum num2){
	if(num1.num[0]=='+'){		//....0 false 1 true
		if(num2.num[0]=='-')return(1);
		if(num1.len>num2.len)return(1);
		if(num1.len<num2.len)return(0);
		for(int i=1;i<num1.len;i++)
			if(num1.num[num1.len-i]<num2.num[num2.len-i])return(0);
		return(1);
	}
	if(num1.num[0]=='-'){
		if(num2.num[0]=='+')return(0);
		if(num1.len>num2.len)return(0);
		if(num1.len<num2.len)return(1);
		for(int i=1;i<num1.len;i++)
			if(num1.num[num1.len-i]<num2.num[num2.len-i])return(1);
		return(0);
	}
	return(0);
}
int operator==(lanum num1,lanum num2){
	if(num1.len!=num2.len)return(0);
	for(int i=0;i<num1.len;i++)
		if(num1.num[i]!=num2.num[i])return(0);
	return(1);
}
int operator<(lanum num1,lanum num2){
	if(num1>num2)return(0);
	if(num1==num2)return(0);
	return(1);
}
lanum operator+(lanum num1,lanum num2){
	if(num1.num[0]=='-'){num1.complement();num1.normalise();}
	if(num2.num[0]=='-'){num2.complement();num2.normalise();}

	///////////////////////////////////
	char carry='0';
	lanum newnum;
	int lar_len=num1.len>num2.len?num1.len+1:num2.len+1;
	newnum.num = new char[lar_len];
	if(newnum.num==NULL){
		cout<<"Not enough memory";
		exit(0);
	}
	char digit1,digit2;int sum;
	for(int i=1;i<lar_len;i++){
		if(i>(num1.len-1)){
			if(num1.num[0]=='+')digit1='0';
			else digit1='9';
		}
		else	digit1=num1.num[i];

		if(i>(num2.len-1)){
			if(num2.num[0]=='+')digit2='0';
			else digit2='9';
		}
		else	digit2=num2.num[i];
		sum=digit1+digit2+carry-48-48-48;
		newnum.num[i]=(sum%10)+48;
		carry=(sum/10)+48;
	}
	newnum.len=lar_len;
/*	if(carry=='0')newnum.len=lar_len-1;
	else {	newnum.num[i]=carry;
			newnum.len=lar_len;
		}*/
	if(num1.num[0]=='+'&&num2.num[0]=='+'){
		newnum.num[0]='+';
		newnum.normalise();
		return(newnum);
	}
//	newnum.len=lar_len;
	if(newnum.num[newnum.len]!='9'){
		newnum.num[0]='+';
		newnum.normalise();
	}
	else{
		newnum.num[0]='-';
		newnum.normalise();
		newnum.complement();
		newnum.num[0]='+';
		newnum.normalise();
		newnum.num[0]='-';
	}
	return(newnum);
}
lanum operator-(lanum num1,lanum num2){
	if(num2.num[1]=='0'&&num2.len==2);
	else	num2.num[0]=(num2.num[0]=='-'?'+':'-');
	return(num1+num2);
}
lanum operator*(lanum num1,lanum num2){
	int len1=num1.len,len2=num2.len;

	lanum temp;
	temp.len=len1+len2-1;
	temp.num=new char[temp.len];
	temp.num[0]='+';

	lanum final;
	final.num=new char[2];
	final.num[0]='+';final.num[1]='0';
	final.len=2;

	for(int i=1;i<len2;i++){
		//....put (i-1) zeros at end of temp
		for(int j=0;j<i-1;j++) temp.num[j+1]='0';
		char carry='0',sum='0';

		//.....multiply num2.num[i] to num1.num and store in
		//.....temp from (i)th position onward
		for(j=1;j<=len1-1;j++){
			sum=(num2.num[i]-48)*(num1.num[j]-48);
			sum=sum+(carry-48);
			temp.num[i+(j-1)]=(sum%10)+48;
			carry=(sum/10)+48;
		}

		temp.num[i-1+len1]=carry;
		temp.len=i+len1;
		final=final+temp;
	}
	final.normalise();
	char sign;
	if((num1.num[0]=='+'&&num2.num[0]=='+')||
	   (num1.num[0]=='-'&&num2.num[0]=='-'))sign='+';
	else sign='-';
	final.num[0]=sign;
	return(final);
}
void main()
{
	clrscr();
	lanum a,b;
	a.getnum();
	b.getnum();

	cout<<"\na = ";a.display();
	cout<<"\nb = ";b.display();
	cout<<"\na+b = ";(a+b).display();
	cout<<"\na-b = ";(a-b).display();
	cout<<"\na*b = ";(a*b).display();
	cout<<"\na>b = "<<(a>b);
	cout<<"\na<b = "<<(a<b);
	cout<<"\na==b = "<<(a==b);
	getch();
}