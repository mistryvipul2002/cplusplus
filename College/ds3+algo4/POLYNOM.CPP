#include<iostream.h>
#include<process.h>
#include<bios.h>
#include<alloc.h>
#include<stdio.h>
#include<conio.h>
void out()
{
 cout<<"\n\nOut of memory.......";
 cout<<"\nProgram will be aborted......";
 bioskey(0);
 exit(1);
}
//.......class polynomial that implements polynomial addn and multn
class polynomial
{  public:int **mat;
	  int xdeg,ydeg;
	  void initma();
	  void init();
	  void print_poly();
	  ~polynomial();
};
void product(polynomial &,polynomial &);
void sum(polynomial &,polynomial &);//...a simple function
void polynomial::~polynomial()
{ //cout<<"\nDestructor at work.\n";
  for(int i=0;i<=xdeg;i++)delete mat[i];
  delete []mat;
}
void polynomial::initma()
{   //........memory allocation
//    cout<<"\nConstructor at work.\n";
    mat=new int*[xdeg+1];
    if(!mat)out();
    for(int i=0;i<=ydeg;i++){ mat[i]=new int[ydeg+1];if(!mat[i])out();}
}
void polynomial::init()
{    //........data entry
    cout<<"Enter highest degree of x.......";cin>>xdeg;
    cout<<"Enter highest degree of y.......";cin>>ydeg;
    initma();
    cout<<"\n\nEnter coefficients for polynomial of \n"
    <<xdeg<<" degree in x and \n"<<ydeg<<" degree in y\n\n\n";
    for(int i=0;i<=xdeg;i++)
      for(int j=0;j<=ydeg;j++)
       { //.....enter coefficient of x^i,y^j
	 cout<<"\n\n";
	 if(i==0&&j==0) cout<<"Enter the constant term ";
	 else
	 {
	 cout<<"Enter the coefficient of ";
	 if(i!=0){ cout<<"x";
		   if(i!=1)
		    { gotoxy(wherex(),wherey()-1);
		      cout<<i;
		      gotoxy(wherex(),wherey()+1);
		    }
		 }
	 if(j!=0){ cout<<"y";
		   if(j!=1)
		    { gotoxy(wherex(),wherey()-1);
		      cout<<j;
		      gotoxy(wherex(),wherey()+1);
		    }
		 }
	 }
	 cout<<" :-  ";
	 cin>>mat[i][j];
       }
}
void polynomial::print_poly()
{
 int t=0;
 for(int i=0;i<=xdeg;i++)//.......x
  for(int j=0;j<=ydeg;j++)//.......y
   if(mat[i][j]!=0)
     { int coeff=mat[i][j];
       //.....print coefficient
       if(wherex()>=70)cout<<"\n\n";
       if(t!=0)if(coeff>0)cout<<"+ ";
       if(coeff==1) {  if(i==0&&j==0)cout<<"1"; }
       else  cout<<coeff;
       //.....print x and y with powers
       if(i!=0)  { cout<<"x";
		   if(i!=1)
		    { gotoxy(wherex(),wherey()-1);
		      cout<<i;
		      gotoxy(wherex(),wherey()+1);
		    }
		 }
       if(j!=0)  { cout<<"y";
		   if(j!=1)
		    { gotoxy(wherex(),wherey()-1);
		      cout<<j;
		      gotoxy(wherex(),wherey()+1);
		    }
		 }
       cout<<" ";
       t++;
     }
}
void sum(polynomial &poly1,polynomial &poly2)//...a simple function
{ polynomial poly3;
  //......poly3 must be able to accomodate all the terms of poly1 and poly2
  if(poly1.xdeg>poly2.xdeg)poly3.xdeg=poly1.xdeg;
  else poly3.xdeg=poly2.xdeg;
  if(poly1.ydeg>poly2.ydeg)poly3.ydeg=poly1.ydeg;
  else poly3.ydeg=poly2.ydeg;
  //.......now allocate memory to poly3
  poly3.initma();
  for(int i=0;i<=poly3.xdeg;i++)
   for(int j=0;j<=poly3.ydeg;j++)
     { int bool1= i<=poly1.xdeg && j<=poly1.ydeg; //....i,j lie in first
       int bool2= i<=poly2.xdeg && j<=poly2.ydeg; //....i,j lie in second
       if(bool1 && bool2) poly3.mat[i][j]=poly1.mat[i][j]+poly2.mat[i][j];
       else if(bool1) poly3.mat[i][j]=poly1.mat[i][j];
       else if(bool2) poly3.mat[i][j]=poly2.mat[i][j];
       else poly3.mat[i][j]=0;
     }
 poly3.print_poly();
}
void product(polynomial &poly1,polynomial &poly2)
{
 polynomial poly3;
 poly3.xdeg=poly1.xdeg+poly2.xdeg;
 poly3.ydeg=poly1.ydeg+poly2.ydeg;
 poly3.initma();
 for(int i=0;i<=poly3.xdeg;i++)
   for(int j=0;j<=poly3.ydeg;j++)
      poly3.mat[i][j]=0;
 //.....take a number from first polynomial
 for(i=0;i<=poly1.xdeg;i++)
  for(j=0;j<=poly1.ydeg;j++)
   //......multiply this to all terms in second polynomial if it is not 0
   if(poly1.mat[i][j]!=0)
    { int prod=1,xpow=0,ypow=0; //....final term is stored in this
      for(int x=0;x<=poly2.xdeg;x++)
       for(int y=0;y<=poly2.ydeg;y++)
	//.......if this is 0 then also terminate multiplication process
	if(poly2.mat[x][y]!=0)
	 { xpow=i+x; //.....x power of final term
	   ypow=j+y; //.....y power of final term
	   prod=poly1.mat[i][j]*poly2.mat[x][y];
	   poly3.mat[xpow][ypow]+=prod;
	 }
    }
 poly3.print_poly();
}
void main()
{
 clrscr();
 //............program of polynomials
 //......enter two polynomials
 cout<<"Enter first polynomial.... \n";
 polynomial poly1;
 poly1.init();
 clrscr();
 cout<<"First polynomial is....\n\n";
 poly1.print_poly();
 bioskey(0);
 clrscr();
 cout<<"Enter second polynomial.... \n";
 polynomial poly2;
 poly2.init();
 clrscr();
 cout<<"Second polynomial is....\n\n";
 poly2.print_poly();
 bioskey(0);

 //.........print sum of them
 clrscr();
 cout<<"Polynomial 1 :-\n\n";
 poly1.print_poly();
 cout<<"\n\n\nPolynomial 2 :-\n\n";
 poly2.print_poly();
 cout<<"\n\n\nSum = \n\n";
 sum(poly1,poly2);
 bioskey(0);

 //........now multiply
 clrscr();
 cout<<"Polynomial 1 :-\n\n";
 poly1.print_poly();
 cout<<"\n\n\nPolynomial 2 :-\n\n";
 poly2.print_poly();
 cout<<"\n\n\nProduct = \n\n";
 product(poly1,poly2);
 bioskey(0);
}