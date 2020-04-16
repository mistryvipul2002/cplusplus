#include<conio.h>
#include<dos.h>
#include<iostream.h>
#define MAX 90000
class matrix
{	public:
		int mat[10][10];
		void print(int order)
		{	for(int i=0;i<order;i++)
			{	for(int j=0;j<order;j++)
					cout<<mat[i][j]<<"\t";
				cout<<"\n";
			}
		}
		void enter(int order)
		{	for(int i=0;i<order;i++)
				for(int j=0;j<order;j++)
					cin>>mat[i][j];
		}
};
inline matrix strassen(matrix,matrix,int);
inline matrix matadd(matrix,matrix,int);
inline matrix matsub(matrix,matrix,int);
void main()
{
	clrscr();
	cout<<"Enter order of matrices.....";
	int temp,ord;
begin:	cin>>ord;temp=2;
	while(1)
	{	if(ord%temp!=0){cout<<"The order should be in form of 2^n....\n";goto begin;}
		temp=temp*2;
		if(temp>ord)break;
	}
	matrix a,b,c_strassen,c_ncube;
	cout<<"Enter elements of matrix a..........\n";
	a.enter(ord);
	cout<<"Enter elements of matrix b..........\n";
	b.enter(ord);

	//......calculate time required by the program
	time t1,t2,t3,t4;
	int i,j,k;

	gettime(&t1);
	for(long int cou=0;cou<MAX;cou++)
		c_strassen=strassen(a,b,ord);
	gettime(&t2);

	gettime(&t3);
	for(cou=0;cou<MAX;cou++)
	{   for(i=0;i<ord;i++)
			for(j=0;j<ord;j++)
			{   c_ncube.mat[i][j]=0;
				for(k=0;k<ord;k++)
					c_ncube.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
			}
	}
	gettime(&t4);

	cout<<"\n\nMatrix c=a*b by strassen is :-\n";
	c_strassen.print(ord);
	cout<<"\nMatrix c=a*b by simple algorithm is :-\n";
	c_ncube.print(ord);

	cout<<"\n\nThe time taken by strassen algorithm when run "<<MAX<<" times = \n";
	int hund=t2.ti_sec*100+t2.ti_hund-t1.ti_sec*100-t1.ti_hund;
	cout<<int(hund/100)<<" seconds "<<int(hund%100)<<" milliseconds \n";

	cout<<"\n\nThe time taken by simple algorithm when run "<<MAX<<" times = \n";
	hund=t4.ti_sec*100+t4.ti_hund-t3.ti_sec*100-t3.ti_hund;
	cout<<int(hund/100)<<" seconds "<<int(hund%100)<<" milliseconds \n";

	getch();
}
matrix matadd(matrix a,matrix b,int order)
{	matrix c;
	for(int i=0;i<order;i++)
		for(int j=0;j<order;j++)
			c.mat[i][j]=a.mat[i][j]+b.mat[i][j];
	return(c);
}
matrix matsub(matrix a,matrix b,int order)
{	matrix c;
	for(int i=0;i<order;i++)
		for(int j=0;j<order;j++)
			c.mat[i][j]=a.mat[i][j]-b.mat[i][j];
	return(c);
}
matrix strassen(matrix a, matrix b,int n)
{	matrix c;
	if(n==1)
	{	c.mat[0][0]=a.mat[0][0]*b.mat[0][0];
		return(c);
	}
		
	matrix a11,a12,a21,a22,b11,b12,b21,b22;
	for(int i=0;i<n/2;i++)
		for(int j=0;j<n/2;j++)
		{	a11.mat[i][j]=a.mat[i][j];
			b11.mat[i][j]=b.mat[i][j];

			a12.mat[i][j]=a.mat[i][j+n/2];
			b12.mat[i][j]=b.mat[i][j+n/2];

			a21.mat[i][j]=a.mat[i+n/2][j];
			b21.mat[i][j]=b.mat[i+n/2][j];

			a22.mat[i][j]=a.mat[i+n/2][j+n/2];
			b22.mat[i][j]=b.mat[i+n/2][j+n/2];
		}

	matrix p,q,r,s,t,u,v;
	p=strassen(matadd(a11,a22,n/2),matadd(b11,b22,n/2),n/2);
	q=strassen(matadd(a21,a22,n/2),b11,n/2);
	r=strassen(a11,matsub(b12,b22,n/2),n/2);
	s=strassen(a22,matsub(b21,b11,n/2),n/2);
	t=strassen(matadd(a11,a12,n/2),b22,n/2);
	u=strassen(matsub(a21,a11,n/2),matadd(b11,b12,n/2),n/2);
	v=strassen(matsub(a12,a22,n/2),matadd(b21,b22,n/2),n/2);

	matrix c11,c12,c21,c22;
	c11=matsub(matadd(matadd(p,s,n/2),v,n/2),t,n/2);
	c12=matadd(r,t,n/2);
	c21=matadd(q,s,n/2);
	c22=matsub(matadd(matadd(p,r,n/2),u,n/2),q,n/2);

	for(i=0;i<n/2;i++)
		for(j=0;j<n/2;j++)
		{	c.mat[i][j]=c11.mat[i][j];
			c.mat[i][j+n/2]=c12.mat[i][j];
			c.mat[i+n/2][j]=c21.mat[i][j];
			c.mat[i+n/2][j+n/2]=c22.mat[i][j];
		}
	return(c);
}