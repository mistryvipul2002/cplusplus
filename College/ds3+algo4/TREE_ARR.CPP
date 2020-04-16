//....This program enters and prints the binary tree using array
#include<iostream.h>
#include<conio.h>
#include<math.h>
#define LEFT 0
#define RIGHT 1
void print(char*,int,int); //...function prototype
int level(int);
int nodes; //...denotes total number of nodes in the tree
void main()
{
 clrscr();
 cout<<"Enter no of levels to be used in tree ?";
 int level;
 cin>>level;
 cout<<"\n\n";
 nodes=pow(2,level)-1;   //.....2^(level)-1  are total nodes
 char *tree=new char[nodes];   //...dynamically allocate space for array
 for(int i=0;i<nodes;i++)tree[i]=0;  //...initialise all by 0
 //...loop for entering all elements
 for(i=0;i<nodes;i++)
   {  if(i==0){ cout<<" Enter root node.......";cin>>tree[i];}
      else { if(tree[(i-1)/2]!='#')
	       {  if(i%2==1)cout<<"Enter left node of "<<tree[i/2];
		  else cout<<"Enter right node of "<<tree[(i-1)/2];
		  cout<<" (# to put empty)........";
		  cin>>tree[i];
	       }
	     else tree[i]='#';
	   }
   }
 //....now print the tree
 clrscr();
 cout<<"Binary Tree you entered is :- \n";
 print(tree,0,0);   //....recursive function
 delete []tree;      //...deallocate the memory
 getch();
}
//...recursive function which prints the element at position pos and
//...tree associated with it  at that position
void print(char *tree,int pos,int status)
{
 if(pos>=nodes)return;  //...is pos exceeds total nodes return
 //...leave space equal to the level of pos element
 for(int i=0;i<level(pos)-2;i++)cout<<" ";
 if(tree[pos]=='#')      //...if element is # print null
    { if(status==LEFT)cout<<"Ã";else cout<<"À";
      cout<<"null\n"; return;
    }
 else     //...else print the element
    { if(pos!=0) if(status==LEFT)cout<<"Ã";else cout<<"À";
      cout<<tree[pos]<<"\n";
    }
 print(tree,2*pos+1,LEFT);       //....call function again for left child
 print(tree,2*pos+2,RIGHT);     //....call function again for right child
}
//...this function returns the level of particular element at position pos
int level(int pos)
{
 int cou=0;  pos++;
 while(pos)  //...while pos donot contain 0
 { pos=pos/2;
   cou++;     //...increase cou
 }
 return(cou);  //...cou is level of element
}