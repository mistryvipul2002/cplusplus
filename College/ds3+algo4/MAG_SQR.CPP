#include<iostream.h>
void magic(int n)
{
 const int msize=51;
 int sqr[msize][msize],k,l;
 if(n>msize||n<1)
   {  cerr<<"Error!....n out of range\n";
      return;
   }
 else if(!(n%2)){cerr<<"Error!...n is even\n";return;}

 for(int i=0;i<n;i++)
	{	for(int j=0;j<n;j++)
		   sqr[i][j]=0;
	}
 sqr[0][(n-1)/2]=1;

 int key=2;i=0;int j=(n-1)/2;
 while(key<=n*n)
 {
  if(i-1<0)k=n-1;else k=i-1;
  if(j-1<0)l=n-1;else l=j-1;
  if(sqr[k][l])i=(i+1)%n;
  else {   i=k;
	   j=l;
       }
  sqr[i][j]=key;
  key++;
 }
 cout<<"Magic Square of size "<<n<<"\n\n";
 for(i=0;i<n;i++)
   {
   for(int j=0;j<n;j++)
   cout<<sqr[i][j]<<"\t";
   cout<<"\n\n\n";
   }
}
void main()
{
 cout<<"Enter order of square ?  ";
 int order;
 cin>>order;
 magic(order);
}