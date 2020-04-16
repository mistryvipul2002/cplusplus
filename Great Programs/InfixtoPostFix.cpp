//.....This is a program to convert an infix expression into
//.....postfix expression and evaluate it also.
#include<string.h>
#include<math.h>
#include<iostream.h>
#include<bios.h>
#include<conio.h>
#define Maxsize 70
class stack;   //....to tell  compiler that a class stack exists
struct operand_str
{ float value;   //.....value of operand
  char ch;       //.....operand
};
/*********************************************************/
//......global functions
int correct(char*);//.checks entered string is correct arithmetic expr or not
int is_alpha(char c)  //.....check if c is from 'a' to 'z' i.e. a proper
{ if(c>='a'&&c<='z')return(1);    //....variable name
  else return(0);
}
stack convert_postfix(char *);
stack convert_suitable(char *);
float evaluate(stack);
void find_operands(operand_str *,stack,int &);
/*********************************************************/
//...union to store no. and operands both
union u{ float f;  //....to store a number
	 char c;   //...to store operands
       };
struct node      //....structure to store elements of expression
{  u data;
   int type;//..0 means a number....1 means binary operator...2 means operand.
	    //..3 means unary operator..4 means left bracket '('....5 means right bracket ')'
};
/***********************************************************/
//....structure to store operators
#define OP_SIZE 8
struct oper{ char op;
	     int priority;
	   };
const int pr=0;    //...pr is priority of operators
oper oper_list[]={ {'+',pr},{'-',pr},{'*',pr+1},{'/',pr+1},
		   {'^',pr+3},{'S',pr+3},{'C',pr+3},{'T',pr+3}};
int check_type(char ch)  //....check type of ch as unary or binary operator
{  if(ch=='S'||ch=='C'||ch=='T')return(3);
   else return(1);
}
int get_pr(node n)     //...return priority of operator
{ for(int i=0;i<OP_SIZE;i++)
   if(n.data.c==oper_list[i].op)return(oper_list[i].priority);
  return(pr);
}

/*********************************************************/
//...........class stack
class stack
{ 	node array[Maxsize];
	int top;
 public:stack();
	int pop(node*);   //...pop and put in node*
	int push(node*);  //...push argument in stack
	void read_bottom(); //...read stack from bottom
	int check_top();//...check if top of stack is operator or not
	node get_top();
	void set_reverse();
	void put_thisch(char,int);  //....put ch into stack
};
//.......function definations
node stack::get_top()    //..returns top node but donot pop it
{ node nod;
  nod=array[top];
  return(nod);
}
int stack::check_top()       //....if top element is an operator return 1
{ if(array[top].type==1||array[top].type==3)
     return(1);
  else return(0);
}
stack::stack()  		     //....constructor
{ top=-1;}
int stack::pop(node *item)           //....pop
{ if(top==-1)return(0);
  else { *item=array[top];
	 top=top-1;
	 return(1);
       }
}
int stack::push(node *item)         //.....push
{ if(top==Maxsize-1)return(0);
  else { top=top+1;
	 array[top]=*item;
	 return(1);
       }
}
void stack::read_bottom()            //.....read from bottom to top
{ for(int i=0;i<=top;i++)
    if(array[i].type==0)cout<<array[i].data.f;
    else cout<<array[i].data.c;
  cout<<"\n";
}
void stack::set_reverse()  //.....make stack to be reversed
{ stack st=*this;   //....make another equal stack 'st' temporary
  for(int i=0;i<=st.top;i++)
     st.array[i]=this->array[st.top-i];
  *this=st;
}
void stack::put_thisch(char ch,int type)  //....put ch into stack
{ node nod;
  nod.data.c=ch;nod.type=type;
  push(&nod);
}
/***************************************************************/
void show(node n,stack stk_oper,stack stk_post)  //..show stacks operator and postfix
{
  cout<<"Symbol scanned --->";
  if(n.type==0)cout<<n.data.f;
  else cout<<n.data.c;
  cout<<"\nStack operators-->";stk_oper.read_bottom();
  cout<<"Stack postfix-->";stk_post.read_bottom();
  cout<<"----------------------------------Press any key to continue\n";
  bioskey(0);
}
/*************************************************************/
void main()
{ clrscr();
  char s[Maxsize];       //....s contains the infix expression
again:cout<<"\nEnter the infix expression without any space ? \n";
  cout<<"Rules :-\n";
  cout<<"1) Use lowercase alphabets for variables\n";
  cout<<"2) You can enter floating point numbers also.\n";
  cout<<"3) Use S,C and T for sin, cos and tan functions\n";
  cout<<"4) You can give {},[] or () brackets.\n";
  cin>>s;
  if(!correct(s))goto again;  //....check if expr. is correct
  stack stk_post=convert_postfix(s);
  cout<<"\nWant to evaluate the expresion(y/n)? ";
  char ch;cin>>ch;
  if(ch=='y'||ch=='Y')
     {  float f=evaluate(stk_post);
	cout<<"\n\nValue of expression is = "<<f;
     }
  bioskey(0);
}
stack convert_postfix(char *s)
{ clrscr();
  stack stk_expr=convert_suitable(s);
  stack temp=stk_expr;   //...temporarily store it
  cout<<"\nThe expression you entered is :-\n";
  stk_expr.read_bottom();
  stk_expr.set_reverse();   //.....reverse the entire expr
  cout<<"\nWant to see step by step process for postfix conversion(y/n)? ";
  char cho;cin>>cho;int flag=0;
  if(cho=='y'||cho=='Y')flag=1;//...now flag will determine the procedure
  /******************************************************************/
  //....now we get our expr in 'stk_expr' in a suitable form
  //....now we find postfix expr and store in 'stk_post'
  //....and we also use 'stk_oper' to store operators
  stack stk_oper,stk_post;   //...stack for operators
  node nod;
  while(stk_expr.pop(&nod))  //....get element from expr in nod
  {
   if(nod.type==2)  //...operand
	 { stk_post.push(&nod);  //...push it in postfix stack
	   if(flag)show(nod,stk_oper,stk_post);}
   if(nod.type==4)   //....left parentheses
	 {  stk_oper.push(&nod);
	    if(flag)show(nod,stk_oper,stk_post);}
    if(nod.type==1||nod.type==3)   //....operator encountered in nod
      { //.....now come in operator stack which contain operators ,'('and')'
	node nod_next;
aga:    //.....if top element is operator or not and has
	//......higher or same precedence as of nod
	node nod_top=stk_oper.get_top();   //...get top element
	if(stk_oper.check_top() && get_pr(nod_top)>= get_pr(nod))
	      { stk_oper.pop(&nod_next);  //....pop from operator
		stk_post.push(&nod_next); //....and push in postfix expr
		goto aga;   //....again go for checking for more operators
	      }
	else   //.....if of low precedence or if not an operator
	      { stk_oper.push(&nod);  //...push it into operator stack
		if(flag)show(nod,stk_oper,stk_post);
		continue;
	      }
      }
    if(nod.type==5)    //...right parentheses
      { node nod_next;
agai:	if(stk_oper.check_top())  //....top of stk_oper is operator
	  {  stk_oper.pop(&nod_next);//.pop and push until '(' is encountered
	     stk_post.push(&nod_next);
	     goto agai;
	  }
	else //......'(' encountered so remove it
	  stk_oper.pop(&nod_next);
	if(flag)show(nod,stk_oper,stk_post);
      }
    if(nod.type==0)  //...a number
      { stk_post.push(&nod);  //...push it in postfix stack
	if(flag)show(nod,stk_oper,stk_post);}

  }//....end of while
  cout<<"Press any key to continue..........";
  clrscr();
  cout<<"Original expression is======>\n";
  temp.read_bottom();
  cout<<"Postfix expression is======>\n";
  stk_post.read_bottom();
  return(stk_post);
}
stack convert_suitable(char *s)
{ int n=strlen(s);   //.....n gives the length of expression
  //.....now scan expr. and store it in a more suitable form
  //.....in which everything is clear as to which is operator,operand etc.
  stack stk_expr;    //.....stack to store expression
  stk_expr.put_thisch('(',4);  //....push '('
  int i=0;
  while(1)
  { char ch=s[i];    //.....read a character in ch
    if(is_alpha(ch))   //.....is ch is alphabet take it as a variable
       stk_expr.put_thisch(ch,2);  //...put this character in stack as operand
    if(ch=='(') stk_expr.put_thisch(ch,4);  //...put this character in stack as (
    if(ch==')') stk_expr.put_thisch(ch,5);  //...put this character in stack as )
    for(int j=0;j<OP_SIZE;j++)     //....if ch is operator first check its type
       if(ch==oper_list[j].op)stk_expr.put_thisch(ch,check_type(ch));//.and then put in stack

    //....now only possibilty remains of numbers
    if(s[i]>='0'&&s[i]<='9')   //....if present character is a number
    {  char str[10];int c=0;    //...create a string
       while(1)
       { if(s[i-1]=='e')str[c++]=s[i++];//if earlier letter was 'e' store current letter anyhow
	 if((s[i]>='1'&&s[i]<='9')||s[i]=='.'||s[i]=='e')  //....extract digits from s
	    str[c++]=s[i++];  //...and store them in string str
	 else break;
       }
       str[c]='\0'; //.....end the string by '\0'
       node nod;
       nod.data.f=atof(str);//.convert string of no. str into float no.
		      //...using atof and then store complete no. in array as element
       nod.type=0;   //....set type of this element as 0
       stk_expr.push(&nod);
       i--;    //....while making str i was increased by 1
    }
    if(i++>=n)break;  //...if i becomes greater than n break i.e. expr has ended
  }  //.....end of while loop i.e. expr is scanned
  stk_expr.put_thisch(')',5);       //...insert ')' at end
  return(stk_expr);
}
int correct(char *s)
{ //....write code to check whether expression entered is correct or not
  int left_br[3]={0,0,0};   //.....for (, { and [ brackets
  int right_br[3]={0,0,0};
  int variab=0;
  for(int i=0;i<strlen(s);i++)
  { if(s[i]=='(')left_br[0]++;if(s[i]=='{')left_br[1]++;if(s[i]=='[')left_br[2]++;
    if(s[i]==')')right_br[0]++;if(s[i]=='}')right_br[1]++;if(s[i]==']')right_br[2]++;
    if(s[i]=='{'||s[i]=='[')s[i]='(';//convert all '{','[' brackets into '('
    if(s[i]=='}'||s[i]==']')s[i]=')';
    //.....if a variable is encountered
    if((i>0&&i<Maxsize)&&is_alpha(s[i]))  //...check adjacent characters
      if(is_alpha(s[i-1])||is_alpha(s[i+1])) //...whether alphabets or not
		 variab=1;
  }
  if(variab){cout<<"Error----->Two or more variables together.\n";return(0);}
  if(left_br[0]!=right_br[0]||left_br[1]!=right_br[1]||left_br[2]!=right_br[2])
  { cout<<"Error-----> Braces not matched.....\n";return(0);}

  //.....when expression has passed all tests it will come here
  return(1);
}
float evaluate(stack stk_post)
{   stk_post.put_thisch(')',5);  //....add ')' at end of postfix expr as a sentinel
  stk_post.set_reverse();   //....reverse the postfix expr
  operand_str operand[Maxsize];   //.....to store operand and their values
  int counter=-1;
  find_operands(operand,stk_post,counter);

  //......now we get operands and their values in operand array
  node nod;
  stack value;   //..stores final value of expression
  while(stk_post.pop(&nod))  //....read value in nod
  { if(nod.data.c==')')break;  //...if ')' encountered break out of loop
    if(nod.type==2)   //...if operand encountered
      { for(int i=0;i<=counter;i++)        //..check for it in list
	 { if(nod.data.c==operand[i].ch)   //...if matched
	    { node n;n.data.f=operand[i].value;n.type=2;
	      value.push(&n);    //....push value of operand
	      break;
	    }
	 }
      }
    if(nod.type==0)    //.....if a number is encountered
	value.push(&nod);
    if(nod.type==3)    //....unary operator
      { node n;value.pop(&n); //...pop a value from 'value' stack
	//...apply unary operation on it
	switch(nod.data.c)
	{ case 'S'://....sine operation
		   n.data.f=sin(n.data.f);
		   value.push(&n);
		   break;
	  case 'C'://....cos operation
		   n.data.f=cos(n.data.f);
		   value.push(&n);
		   break;
	  case 'T'://....tan operation
		   n.data.f=tan(n.data.f);
		   value.push(&n);
	}
      }
    if(nod.type==1)    //....binary operator
      { node a,b,c;c.type=0;//....c will also be a number
	value.pop(&a);value.pop(&b);
	switch(nod.data.c)
	{ case '+':c.data.f=b.data.f+a.data.f;break;
	  case '-':c.data.f=b.data.f-a.data.f;break;
	  case '*':c.data.f=b.data.f*a.data.f;break;
	  case '/':c.data.f=b.data.f/a.data.f;break;
	  case '^':c.data.f=pow(b.data.f,a.data.f);
	}
	value.push(&c);
      }
  } //.....end of while
  //......print the value of last element of value stack
  node temp;value.pop(&temp);
  return(temp.data.f);
}
void find_operands(operand_str *operand,stack stk_post,int &counter)
{ //........construct operand array
  node nod;counter=-1;  //....counter stores position of top element of operand array
  while(stk_post.pop(&nod))
  { if(nod.type==2)      //....if operand
     { //....check if this operand exists in operand list or not
       int flag=0;
       for(int i=0;i<=counter;i++)
	{ if(nod.data.c==operand[i].ch)
	     {  flag=1; break;}
	}
       if(flag==0)   //...donot exist
	{ counter++;
	  operand[counter].ch=nod.data.c;
	  cout<<"Enter the value of variable "<<nod.data.c<<"---> ";
	  cin>>operand[counter].value;
	}
       //....if operand exist leave it
     }
  }//....end of while
}

