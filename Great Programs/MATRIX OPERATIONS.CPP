#include<bios.h>
#include<process.h>
#include<conio.h>
#include<iostream.h>
#include<stdio.h>
/* class matrice to implement all matrix operations*/
class matrice; //....to tell compiler their is a class matrice to be defined later

long int fact(int n);          //...factorial of n
matrice combination(int r,int n);
char check(char no);
void wait();
float value(float *det1[],int or);

class matrice
{
 public:int r;
	int c;
	int flag; //....to find whether there is any data in the matrix
	float **mat;
	matrice(){flag=0;}//....constructer
	void initrc()    //.....initialise row column
		{
		 cout<<"\n\nEnter matrix parameters.......\n";
		 cout<<"Rows = ";cin>>r;
		 cout<<"Columns = ";cin>>c;
		}
	void initma();
	void initde();
	void init()    //....completely initialise
		{ initrc();initma();initde();}
	matrice mat_mult(matrice);
	matrice adj();
	matrice inv();
	matrice tran();
	matrice power(int);
	int rank();
	void identity();
	void display();
/*	~matrice()//..destructer
		{ cout<<"Destructer at work\n";
		delete(mat);}*/
};
matrice matrice::tran()
{
 matrice temp;temp.r=temp.c=r;temp.initma();
 for(int i=0;i<r;i++) for(int j=0;j<c;j++)
     temp.mat[j][i]=mat[i][j];
 return(temp);
}
matrice matrice::power(int n)
{
 matrice temp;temp.r=temp.c=r;temp.initma();
 for(int i=0;i<r;i++) for(int j=0;j<c;j++) temp.mat[i][j]=mat[i][j];
 matrice mat_ret;mat_ret.r=mat_ret.c=r;mat_ret.initma();
 for(i=0;i<r;i++) for(j=0;j<c;j++) mat_ret.mat[i][j]=mat[i][j];
 //...both temp and mat_ret are same as current matrix
 for(i=1;i<n;i++) mat_ret = mat_ret.mat_mult(temp);
 return(mat_ret);
}
matrice matrice::inv()
{
 //......inverse = adj(A)/det(A)
 matrice temp;temp.r=temp.c=r;temp.initma();
 int value=::value(mat,r);    //....value of det
 temp=adj();  //.....temp contains adjoint
 for(int i=0;i<r;i++) for(int j=0;j<c;j++) temp.mat[i][j] /= value;
 return(temp);
}
matrice matrice::mat_mult(matrice mat2)
{ //...returns its multiplication by that
  matrice mat_ret;
  mat_ret.r=r;mat_ret.c=mat2.c;
  mat_ret.initma();
  for(int i=0;i<r;i++)   //......row=r of mat_ret
    {  for(int j=0;j<mat2.c;j++)  //...column= c of mat2
	{  mat_ret.mat[i][j]=0;
	   for(int k=0;k<c;k++)
	   mat_ret.mat[i][j]+=mat[i][k]*mat2.mat[k][j];
	}
   }
 return(mat_ret);
}
matrice matrice::adj()
{
 matrice temp,adj;    //.....cofactor matrice=temp and mat of adjoint =adj
 if(r==1){adj.r=adj.c=1;adj.initma();adj.mat[0][0]=1;return(adj);}
 temp.r=temp.c=r-1;temp.initma();
 adj.r=adj.c=r;adj.initma();
 int p=0,q=0;
 for(int i=0;i<r;i++)  for(int j=0;j<c;j++)   //...for element (i,j) find cofactor
   { p=q=0;                           //...by curbing ith row and jth column
     for(int x=0;x<r;x++)  for(int y=0;y<c;y++) //..traverse each element
       if(x!=i&&y!=j){ temp.mat[p][q]=mat[x][y];if(p==r-2){q++;p=0;}else p++;}
     //...now we get minor for (i,j) in temp
     int value=::value(temp.mat,temp.r);//...value of minor
     //....cofactor is [(-1)^(i+j)]*det(minor)
     if((i+j)%2!=0)value=-value; //....now value is value of cofactor
     //....put this value in main det
     adj.mat[i][j]=value;
   }
 return(adj.tran()); //...adjoint is transpose of this matrix
}
int matrice::rank()
{
 int order;
 if(r<c)order=r; else order=c;
 while(order>=1)
 {
  matrice row=combination(r,order);
  matrice column=combination(c,order);
  for(int i=0;i<row.r;i++)   //...now row[i][] is one combination for row
   { for(int j=0;j<column.r;j++) //..and column[i][] is one combination for column
       {  //.....now fill the determinant
	  matrice deter;deter.r=deter.c=order;deter.initma();//variable determinant
	  for(int p=0;p<order;p++)
	    for(int q=0;q<order;q++)
	      deter.mat[p][q]=mat[row.mat[i][p]][column.mat[j][q]];
	if(value(deter.mat,order)!=0)return(order);
       }
   }
  order--;
 }
 return(0);//....if all emements are 0
}
void matrice::initma()     //... memory allocation
		{
		 //...allocating memory
		 mat=new float*[r];
		 for(int i=0;i<c;i++)
		 mat[i]=new float[c];
		}
void matrice::initde()        //.......data entering
		{
		 //.......entering elements
		 cout<<"\n\nEnter the data for matrix......\n";
		 for(int i=0;i<r;i++)
		  {
		   cout<<"For row "<<i+1<<" enter "<<c<<" elements.....\n";
		   for(int j=0;j<c;j++)
			cin>>mat[i][j];
		  }
		 flag=1;//....means data is entered
		}
void matrice::display()
		{
		 cout<<"\n\n";
		 for(int i=0;i<r;i++)
		   { for(int j=0;j<c;j++)cout<<"\t"<<mat[i][j];
		     cout<<"\n";
		   }
		 wait();
		}
void matrice::identity() {
		 cout<<"\n\nMatrix is...\n\n";
		 if(r==1)cout<<"\t-> Row Matrix.\n";
		 if(c==1)cout<<"\t-> Column  Matrix.\n";
		 if(r==c)cout<<"\t-> Square  Matrix / Determinant.\n";
		 int tot_zero=0,ident_flag=1,diag_flag=1,sym_flag=1;
		 int sk_sym_flag=1,up_diagonal_flag=1,low_diagonal_flag=1;
		 int orth_flag=1;
		 matrice trans=tran();matrice invs=inv();
		 for(int i=0;i<r;i++)
		   for(int j=0;j<c;j++)
		     { if(mat[i][j]==0){tot_zero++;}
		       if((i!=j&&mat[i][j]!=0)||(i==j&&mat[i][j]!=1)||(r!=c))
			  ident_flag=0;
		       if((i!=j&&mat[i][j]!=0)||(i==j&&mat[i][j]==0)||(r!=c))
			  diag_flag=0;
		       if((mat[i][j]!=mat[j][i])||(r!=c))
			  sym_flag=0;
		       if((mat[i][j]!=-mat[j][i])||(r!=c))
			  sk_sym_flag=0;
		       if(r!=c || trans.mat[i][j]!=invs.mat[i][j])orth_flag=0;
		       if(mat[i][j]!=0&&i>j)up_diagonal_flag=0;
		       if(mat[i][j]!=0&&i<j)low_diagonal_flag=0;
		     }
		 if(tot_zero==r*c)cout<<"\t-> Zero or Null Matrix.\n";
		 if(ident_flag==1)cout<<"\t-> Identity or Unit Matrix of order "<<c<<"\n";
		 if(diag_flag==1)cout<<"\t-> Diagonal Matrix of order "<<c<<"\n";
		 if(sym_flag==1)cout<<"\t-> Symmetric Matrix of order "<<c<<"\n";
		 if(sk_sym_flag==1)cout<<"\t-> Skew Symmetric Matrix of order "<<c<<"\n";
		 if(r==c)
		 { if(value(mat,r)==0)cout<<"\t-> Singular and Non-Invertible square matrix of order "<<c<<"\n";
		   else cout<<"\t-> Non-Singular and Invertible square matrix of order "<<c<<"\n";
		 }
		 if(orth_flag==1)cout<<"\t-> Orthogonal Matrix.\n";
		 if(up_diagonal_flag==1)cout<<"\t-> Upper Triangular Matrix of order "<<c<<"\n";
		 if(low_diagonal_flag==1)cout<<"\t-> Lower Triangular Matrix of order "<<c<<"\n";
		 wait();
		}
char check(char no) //....gets a number entered by user from 1 to no
{                 //....and returns it
 fflush(stdin);
 while(1)
 {  char ch=getch();
    if(ch>='a'&&ch<=no)return(ch);
 }
}
void wait()
{
 cout<<"\nPress any key to continue.....";
 bioskey(0);
 cout<<"\n";
}
//...........a recursive fuction to find value of determinant
float value(float *det1[],int or)
{
 int p=0,q=0;
 if(or==1)return(det1[0][0]);
 else
  {
     //...........make a new det of order 1 less than given
     float **det2=new float*[or-1];
     for(int i=0;i<or-1;i++)det2[i]=new float[or-1];
     float sum=0;//........this is the sum of the det
     //.........we have to make det1 of order "or-1"
     //.......this is coloumn 0 on which we are opening determinant
     for(int k=0;k<or;k++)
	{
	  p=0;q=0;
	  //.........for this number with row = k and column as 0
	  //.........form the minor determinant
	  for(int i=0;i<or;i++)     //                         |
	    for(int j=0;j<or;j++)   //.....access each element \/ and -->
	       {
		//....leaving the row and column (k,0)
		if(i!=k&&j!=0)
		  {
		   det2[p][q]=det1[i][j];
		   if(q==or-2){p++;q=0;}
		   else q++;
		  }
	       }
	  //.....so now we get det2
	  //.......add its value to sum;
	  if(k%2==0)sum += det1[k][0]*value(det2,or-1);//......call the function again
					 //...to calculate the value of det2
	  else sum += -det1[k][0]*value(det2,or-1);

	}//........take row of big det one by one to find value
     return(sum);
  }//...........if det if of order larger than 1
}
matrice combination(int r,int n)
{
 //....we have to select n positions out of r numbers from 0 to r-1
 //...total combs possible =         rCn  =             r!
 long int tot =fact(r)/(fact(n)*fact(r-n));//.....  ÄÄÄÄÄÄÄÄÄÄ
 matrice mat_ret;                          //....   n!  (r-n)!
 mat_ret.r=tot;mat_ret.c=n;mat_ret.initma();
 int *arr=new int[n];
 for(int i=0;i<n;i++)arr[i]=i;
 int p=0;
prn:for(i=0;i<n;i++) mat_ret.mat[p][i]=arr[i];
    p++;
 for(i=n-1;i>=0;i--)
   {
     if(arr[i]!=r-(n-i))
      { arr[i]++;
	for(int j=i+1;j<=n-1;j++)arr[j]=arr[j-1]+1;
	goto prn;
      }
   }
 return(mat_ret);
}
long int fact(int n)          //...factorial of n
{
 long int fac=1;
 if(n==0)return(1);
 for(int i=1;i<=n;i++)
    fac=fac*i;
 return(fac);
}
void main()
{
 matrice mat;
 //....main menu
again:clrscr();
 cout<<"\n\n\n\n                   G R A N D   M A T R I X   P R O G R A M\n";
 cout<<"                   =========   ===========   =============\n\n\n";
 cout<<"\t\t\ta) Matrix identification\n";
 cout<<"\t\t\tb) Matrix operations\n";
 cout<<"\t\t\tc) Solve Linear Equation in n variables\n";
 cout<<"\t\t\td) Display Current Matrix\n";
 cout<<"\t\t\te) Find value of determinant\n";
 cout<<"\t\t\tf) Exit\n\n\n";
 fflush(stdin);
cout<<"\t\tPress your choice...........";
 switch(check('f'))
 {
   case 'a':clrscr();
	  //...first decide data from where
	  if(mat.flag!=0)//....if using main menu second (or next) time
	  { cout<<"\n\tPress a to use earlier matrix";
	    cout<<"\n\tPress b to enter new";
	    if(check('b')=='b')mat.init();
	  }
	  else mat.init(); //...if using first time initialise it
	  //....call member function -> identity
	  clrscr();
	  mat.identity();
	  break;
   case 'b'://....new menu
   begin :clrscr();
	  cout<<"\n\n\t\t\tMatrix Operations\n\n";
	  cout<<"\t\ta) Equality of Matrices\n";
	  cout<<"\t\tb) Addition of Matrices\n";
	  cout<<"\t\tc) Subtraction of Matrices\n";
	  cout<<"\t\td) Multiplication of Matrices\n";
	  cout<<"\t\te) Multiplication by Scalar\n";
	  cout<<"\t\tf) Transpose of a Matrix\n";
	  cout<<"\t\tg) Adjoint of Matrix\n";
	  cout<<"\t\th) Inverse of Matrix\n";
	  cout<<"\t\ti) Rank of Matrix\n";
	  cout<<"\t\tj) Find nth power of matrix\n";
	  cout<<"\t\tk) Exit\n\n";
	  cout<<"\t\t\t Press your choice.........";
	  char choice=check('k');
	  if(choice=='k')goto again;
	  matrice mat_final; //...mat in which to put final result

	  //....when proper choice pressed enter the matrix after checking
	  clrscr();
	  cout<<"\n\t\t\tMatrix 1\n";
	  if(choice=='g'||choice=='h'||choice=='j')       //....adjoint and inverse
	  {	   int order;                             //....and nth power
		   //...first decide data from where
		   if(mat.flag!=0 && mat.r==mat.c)//....if using main menu next time
		   { //...in 'h' for inverse mat should be sq and its det not 0
		     if(choice=='h' && value(mat.mat,mat.c)==0)goto vipul1;
		     cout<<"\n\tPress a to use earlier matrix.";
		     cout<<"\n\tPress b to enter new";
		     if(check('b')=='b')goto vipul1;
		   }
		   else       //....enter new matrix
vipul1:		   {  cout<<"\nEnter order of square matrix ? ";
		      cin>>order;mat.r=order;mat.c=order;
		      mat.initma();mat.initde();
		   }
	  }
	  else{   if(mat.flag!=0)//....if using main menu next time
			    {  cout<<"\n\tPress a to use earlier matrix";
			       cout<<"\n\tPress b to enter new";
			       if(check('b')=='b')mat.init();
			    }
		  else mat.init();
	      }
	  //..........each choice briefly taken
	  if(choice<='d')       //....in which two matrices are required
	     { cout<<"\n\n\t\t\tMatrix 2\n";
	       matrice mat_second;

	       if(choice=='d')
	       { mat_second.r=mat.c;
		 cout<<"Rows = "<<mat.c<<" for multiplication to occur";
		 cout<<"\nEnter number of columns ";
		 cin>>mat_second.c;
		 mat_second.initma();mat_second.initde();
	       }
	       else   //....when choice is a,b or c
	       { mat_second.r=mat.r;mat_second.c=mat.c;
		 cout<<"Rows = "<<mat.r;
		 cout<<"\nColumns = "<<mat.c<<" for operation to occur.";
		 mat_second.initma();mat_second.initde();
		 //..now initialise final matrix
		 mat_final.r=mat.r;mat_final.c=mat.c;
		 mat_final.initma();
	       }
	       switch(choice)
		 {
		  case 'a'://....equality
			 clrscr();
			 for(int i=0;i<mat.r;i++)for(int j=0;j<mat.c;j++)
			  if(mat.mat[i][j]!=mat_second.mat[i][j])
			    { cout<<"Matrices not equal.";
			      wait();goto begin;}
			 cout<<"\nMatrices are equal.";wait();
			 goto begin;
		  case 'b'://....addition
			 clrscr();
			 for(i=0;i<mat.r;i++)for(j=0;j<mat.c;j++)
			 mat_final.mat[i][j]=mat.mat[i][j]+mat_second.mat[i][j];
			 cout<<"\nAddition of two matrices is:-\n";
			 break;
		  case 'c'://....subtraction
			 clrscr();
			 for(i=0;i<mat.r;i++)for(j=0;j<mat.c;j++)
			 mat_final.mat[i][j]=mat.mat[i][j]-mat_second.mat[i][j];
			 cout<<"\nSubtraction of two matrices is:-";
			 break;
		  case 'd'://....multiplication
			 clrscr();
			 cout<<"Matrice after multiplication is.......\n\n";
			 mat_final=mat.mat_mult(mat_second);//...pass second matrix
			 break;
		 }
	     }
	  else      //....when only one matrix is required
	    {  switch(choice)
		 {
		  case 'e': //.......mult by scalar
			    clrscr();
			    cout<<"Enter value of scalar ? ";int scalar;cin>>scalar;
			    mat_final.r=mat.r;mat_final.c=mat.c;
			    mat_final.initma();
			    for(int i=0;i<mat.r;i++)
			     for(int j=0;j<mat.c;j++)
				mat_final.mat[i][j]=mat.mat[i][j]*scalar;
			    cout<<"\nMatrix after multiplication by "<<scalar;
			    break;
		  case 'f': //....transpose
			    clrscr();
			    mat_final=mat.tran();
			    cout<<"Transpose of matrix is:-";
			    break;
		  case 'g': //..adjoint
			    clrscr();
			    cout<<"Adjoint of Matrix = ";
			    mat_final=mat.adj();
			    break;
		  case 'h': //..inverse
			    clrscr();
			    cout<<"Inverse of Matrix ";
			    if(value(mat.mat,mat.c)==0)
			    {cout<<"cannot be calculated as det is 0.";bioskey(0);goto begin;}
			    mat_final=mat.inv();
			    break;
		  case 'i': //..rank
			    clrscr();
			    cout<<"Rank of Matrix = "<<mat.rank();
			    wait();
			    goto begin;
		  case 'j': //...nth power
			    clrscr();
			    cout<<"Enter value of n.....";int n;cin>>n;
			    if(n<1){cout<<"\nWrong number.......";goto begin;}
			    mat_final=mat.power(n);
		 }
	    }
	  //....now final matrix is available
	  mat_final.display();
	  cout<<"\nWant this to become current matrix(y/n)? ";
	  char cho=getch();
	  if(cho=='y'||cho=='Y'){mat=mat_final;mat.flag=1;}
	  goto begin;
   case 'c'://....solving simultaneous linear equations
beg:	  clrscr();
	  cout<<"\n\n\t\t\tSolving Simultaneous Linear Equations\n\n";
	  cout<<"\tm = no. of equations\n";
	  cout<<"\tn = no. of variables\n\n";
	  cout<<"\t\ta) By Determinant (m = n)\n";
	  cout<<"\t\tb) Matrix Method (m = n)\n";
	  cout<<"\t\tc) Rank Method (m may be different from n)\n";
	  cout<<"\t\td) Exit\n\n";
	  cout<<"\tPress your choice.............";
	  choice=check('d');
	  if(choice=='d')goto again;
	  clrscr();
	  //....first decide data from where
	  int n;//....n is the number of variables
	  int m;//....m is the number of equations
	  if(choice=='c')
	  {  if(mat.c!=1 && mat.flag!=0)
		    {  cout<<"\n\tPress a to use earlier matrix";
		       cout<<"\n\tPress b to enter new";
		       if(check('b')=='b')goto vipul2;
		    }
	     else goto vipul2;
	  }
	  else   //....when choice is 'a' or 'b'
	  {
	    if(mat.flag!=0 && mat.r+1==mat.c)//....if using main menu next time
		    {  cout<<"\n\tPress a to use earlier matrix";
		       cout<<"\n\tPress b to enter new";
		       if(check('b')=='b')goto vipul2;
		    }
	    else{
vipul2:          cout<<"\n\n\tEnter the number of variables ? ";cin>>n;
		 m=n;
		 if(choice=='c'){cout<<"\tEnter the number of equations ? ";cin>>m;}
		 cout<<"\n\tEquations are of form :-";
		 cout<<"\n\t\t ax + by + ......= c";
		 cout<<"\n\t\t dx + ey + ......= f";
		 cout<<"\n\t\t |    |      |     |";
		 cout<<"\n\tYou have to enter values of a,b,......, and c for first equation...\n\n";
		 //...mat is our main matrix
		 if(choice=='c'){mat.r=m;mat.c=n+1;mat.initma();mat.flag=1;}
		 else {mat.r=n;mat.c=n+1;mat.initma();mat.flag=1;}
		 for(int i=0;i<m;i++)
		   { cout<<"\nEnter the values for equation no. "<<i+1<<"\n";
		     for(int j=0;j<n+1;j++)cin>>mat.mat[i][j];
		     cout<<"\n";
		   }
		}
	  }

	  //....now mat is ready to use
	  switch(choice)
	  {
	   case 'a'://....Cramer's rule
		    //.....D is det of coefficients to left of equality sign D= ³a b³
		    //.....Dj is det by replacing jth column of D by  ³c³       ³d e³
		    //.....					      ³f³
		    matrice D,Dj;D.r=D.c=Dj.r=Dj.c=n;D.initma();Dj.initma();
		    for(int i=0;i<n;i++)for(int j=0;j<n;j++)D.mat[i][j]=mat.mat[i][j];
		    float valueD=value(D.mat,n);//....valueD is value of D
		    float *valueDj=new float[n];

		    for(int k=0;k<n;k++)
		      {  for(int i=0;i<n;i++)for(int j=0;j<n;j++)
			   { if(j==k)Dj.mat[i][j]=mat.mat[i][n];
			     else Dj.mat[i][j]=D.mat[i][j];
			   }
			 valueDj[k]=value(Dj.mat,n);
		      }
		    //..now we get value of D in valueD and of Dj's in valueDj[]
		    if(valueD!=0)//...means equations are consistent
		    { //....print the equations
		      clrscr();
		      cout<<"\n\nEquations are:-\n\t";
		      for(int i=0;i<n;i++)
		      {   for(int j=0;j<n;j++)
			     { if(mat.mat[i][j]>0&&j!=0)cout<<"+";
			       if(mat.mat[i][j]==1){}
			       else if(mat.mat[i][j]==-1)cout<<"-";
			       else if(mat.mat[i][j]==0)continue;
			       else cout<<mat.mat[i][j];
			       putch('a'+j);
			     }
			cout<<"="<<mat.mat[i][n]<<"\n\t";
		      }
		      cout<<"\n\n\t\t\nSolutions are :-\n";
		      for(i=0;i<n;i++)
			 { cout<<"\t";putch('a'+i);
			   cout<<" = "<<valueDj[i]/valueD<<"\n";}
		      wait();goto beg;
		    }
		    else    //..D=0 or inconsistent/infinite solution
		    {
		     for(i=0;i<n;i++)
		      if(valueDj[i]!=0)
		       { cout<<"\n\tGiven Equations are inconsistent with no solution.\n";
			 wait();goto beg;
		       }
		     //....now here eqns are consistent with infinite solutions
		     cout<<"\n\t\tThere are infinite solutions to given eqns.\n";
		     wait();goto beg;
		    }
	   case 'b'://.....matrix method
		    goto beg;
	   case 'c'://.....rank method
		    matrice aug,coef;
		    coef.r=m;coef.c=n;coef.initma();
		    aug.r=m;aug.c=n+1;aug.initma();
		    for(i=0;i<m;i++)for(j=0;j<n;j++)coef.mat[i][j]=mat.mat[i][j];
		    for(i=0;i<m;i++)for(j=0;j<n+1;j++)aug.mat[i][j]=mat.mat[i][j];
		    int raug=aug.rank(),rcoef=coef.rank();

		    clrscr();
		    cout<<"\n\nEquations are:-\n\t";
		    for(i=0;i<m;i++)
		      {   for(int j=0;j<n;j++)
			     { if(mat.mat[i][j]>0&&j!=0)cout<<"+";
			       if(mat.mat[i][j]==1){}
			       else if(mat.mat[i][j]==-1)cout<<"-";
			       else if(mat.mat[i][j]==0)continue;
			       else cout<<mat.mat[i][j];
			       putch('a'+j);
			     }
			cout<<"="<<mat.mat[i][n]<<"\n\t";
		      }

		    cout<<"\n\t";
		    if(raug!=rcoef)
		    {cout<<"Given equation(s) are inconsistent and have no solution.";}
		    else
		     { if(m>=n) //...consistent
			{ if(raug==n)//....unique solution
			   { cout<<"Unique Solution...";
			     //....for each variable
			     for(i=0;i<n;i++)
			      {



			      }
			   }
			  else cout<<"Infinite solns..."<<n-raug<<" arbitrary and "<<raug<<" in terms of them";
			}
		       else
			{ if(raug==m)
			   cout<<"Infinite solns..."<<n-m<<" arbitrary and "<<m<<" in terms of them";
			  else cout<<"Infinite solns..."<<n-raug<<" arbitrary and "<<raug<<" in terms of them";
			}
		     }
		    wait();
		    goto beg;
	  }  //....end of switch(choice)
   case 'd':clrscr();
	  if(mat.flag==0) //....using first time
	  {  cout<<"No current Matrix to display.\n";
	     cout<<"Enter new one(y/n)? ";
	     char ch=getch();
	     if(ch=='y'||ch=='Y')mat.init();
	     else goto again;
	     clrscr();
	  }
	  cout<<"Current Matrix is :-\n";
	  mat.display();
	  break;
   case 'e'://......determinant
	  clrscr();
	  int order;
	  //...first decide data from where
	  if(mat.flag!=0 && mat.r==mat.c) //....if using main menu second (or next) time
	  { cout<<"\n\tPress a to use earlier matrix as a determinant";
	    cout<<"\n\tPress b to enter new";
	    if(check('b')=='b')goto vipul;
	  }
	  else
vipul:	  {  cout<<"\nEnter order of determinant ? ";
		 cin>>order;mat.r=order;mat.c=order;
		 mat.initma();mat.initde();
	  }
	  //.....now det is available
	  cout<<"\n\nValue of determinant is = "<<value(mat.mat,mat.c);
	  wait();
	  break;
   case 'f':exit(0);
 }
 goto again;
}