//....This program enters a list and then makes a tree whose
//....inorder traversal gives us the sorted list
#include<iostream.h>
#include<process.h>
#include<bios.h>
#include<conio.h>
const int LEFT=0,RIGHT=1;
struct node
{  int info;
   node *left;
   node *right;
};
class tree
{  		node *root;
		void search(int,node*);
		void traverse(node*);
   public:      tree();
		node* getnode();
		void create_tree();
		void display();
		void disp(node*,int,int);
};
tree::tree()
{ root->left=root->right=NULL;root->info=0;}
void tree::traverse(node *a)
{ //....now print ldr,dlr,lrd traversals
  if(a->left!=NULL)traverse(a->left);     //....LDR
  cout<<a->info<<" ";
  if(a->right!=NULL)traverse(a->right);
}
void tree::display()
{ clrscr();
  cout<<"Tree formed with the entered list is:- \n";
  cout<<" ";
  disp(root,1,2); //.....give dir 2 not to print any special character
  cout<<"\nPress any key to continue......";
  bioskey(0);
  //....now print traversal
  clrscr();
  cout<<"\n\nSorted list by traversal in inorder LDR :-\n\n";
  traverse(root);
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
   next->right=next->left=NULL;
   return(next);
}
void tree::create_tree()
{
 clrscr();
 cout<<"A Program of Tree by Vipul Mistry\n\n";
 cout<<"Enter range list ? ";int ran;cin>>ran;
 cout<<"Enter the list .......\n";
 int *array=new int[ran];
 for(int i=0;i<ran;i++)
   { cin>>array[i];
     if(i==0)root->info=array[i];
     else search(array[i],root);
   }
}
void tree::search(int numb,node *a)
{ if(a->info<=numb)
    { if(a->right==NULL){ a->right=getnode();
			  a->right->info=numb;
			  return;
			}
      else search(numb,a->right);
    }
  else
    { if(a->left==NULL) { a->left=getnode();
			  a->left->info=numb;
			  return;
			}
      else search(numb,a->left);
    }
}
void main()
{ tree tree1;
  tree1.create_tree();
  tree1.display();
}