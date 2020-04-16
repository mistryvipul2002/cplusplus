//....This program prints a tree entered
//....and then prints its DLR, LDR and LRD traversals
#include<iostream.h>
#include<process.h>
#include<bios.h>
#include<alloc.h>
#include<stdio.h>
#include<conio.h>
const int LEFT=0,RIGHT=1,DLR=1,LDR=2,LRD=3;
struct node
{  char info;
   node *left;
   node *right;
};
class tree
{  		node *root;
		void crea(node*);
		void traverse(int,node*);
   public:      node* getnode();
		void create_tree();
		void display();
		void disp(node*,int,int);
};
void tree::traverse(int tr,node *a)
{ //....now print ldr,dlr,lrd traversals
  switch(tr)
   { case 1:cout<<a->info;                            //....DLR
	    if(a->left!=NULL)traverse(tr,a->left);
	    if(a->right!=NULL)traverse(tr,a->right);
	    break;
     case 2:if(a->left!=NULL)traverse(tr,a->left);     //....LDR
	    cout<<a->info;
	    if(a->right!=NULL)traverse(tr,a->right);
	    break;
     case 3:if(a->left!=NULL)traverse(tr,a->left);    //.....LRD
	    if(a->right!=NULL)traverse(tr,a->right);
	    cout<<a->info;
   }
}
void tree::display()
{ clrscr();
  cout<<"Tree you entered is:- \n";
  cout<<" ";
  disp(root,1,2); //.....give dir 2 not to print any special character
  cout<<"\nPress any key to continue......";
  bioskey(0);
  //....now print traversal
  clrscr();
  cout<<"\n\nTree traversal in preorder DLR :-\n\n";
  traverse(DLR,root);
  cout<<"\n\nTree traversal in inorder LDR :-\n\n";
  traverse(LDR,root);
  cout<<"\n\nTree traversal in postorder LRD :-\n\n";
  traverse(LRD,root);
  cout<<"\n\nPress any key to exit.......";
  bioskey(0);
}
void tree::disp(node *a,int level,int dir)
{ for(int i=1;i<=level-1;i++)cout<<" ";
  if(dir==LEFT)cout<<"Ã";
  else if(dir==RIGHT)cout<<"À";
  cout<<a->info<<"\n";

  if(a->left!=NULL)disp(a->left,level+1,LEFT);
  else { for(int i=1;i<=level;i++)cout<<" ";
	 cout<<"Ãnull\n";
       }

  if(a->right!=NULL)disp(a->right,level+1,RIGHT);
  else { for(int i=1;i<=level;i++)cout<<" ";
	 cout<<"Ànull\n";
       }
}
node* tree::getnode()
{  node *next=new node;
   if(!next){cout<<"\n\nOut of memory";bioskey(0);exit(1);}
   return(next);
}
void tree::create_tree()
{
 clrscr();
 cout<<"A Program of Tree by Vipul Mistry\n\n";
 cout<<"Enter # to enter NULL\n";
 cout<<"\nEnter root node....";
 char ch;cin>>ch;
 if(ch!='#')
    {  root=getnode();
       root->info=ch;
       crea(root);
    }
 else root=NULL;
}
void tree::crea(node *a)
{
  char ch;
  cout<<"Enter left node of "<<a->info<<" .....";
  cin>>ch;
  if(ch!='#')
     {  a->left=getnode();
	a->left->info=ch;
	crea(a->left);
     }
  else a->left=NULL;

  cout<<"Enter right node of "<<a->info<<" .....";
  cin>>ch;
  if(ch!='#')
     {  a->right=getnode();
	a->right->info=ch;
	crea(a->right);
     }
  else a->right=NULL;
}
void main()
{ tree tree1;
  tree1.create_tree();
  tree1.display();
}