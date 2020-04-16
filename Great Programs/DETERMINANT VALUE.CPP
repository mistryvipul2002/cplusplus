#include<iostream.h>
#include<conio.h>
long int value(int *[],int);
void main()
{
 clrscr();
 int ord;
 cout<<"Enter the order of determinant ?";
 cin>>ord;
 int **det;
 det=new int*[ord];
 for(int i=0;i<ord;i++)
     det[i]=new int[ord];
 cout<<"\nEnter the data for determinant......\n";
 for(i=0;i<ord;i++)
 {
  cout<<"For row "<<i+1<<" enter "<<ord<<" elements.....\n";
  for(int j=0;j<ord;j++)
       cin>>det[i][j];
 }
 clrscr();
 cout<<"              A Program By ===========> V I P U L        M I S T R Y\n";
 cout<<"\nThe determinant you entered is :-\n\n";
 for(i=0;i<ord;i++)
   {
    cout<<"\t³\t";
    for(int j=0;j<ord;j++)       cout<<det[i][j]<<"\t";
    cout<<"³\n";
   }
 cout<<"\n\nValue of the determinant is........  "<<value(det,ord);
 getch();
}
int p=0,q=0;
//...........a recursive fuction
long int value(int *det1[],int or)
{
 if(or==1)return(det1[0][0]);
 else
  {
     //...........make a new det of order 1 less than given
     int **det2=new int*[or-1];
     for(int i=0;i<or-1;i++)det2[i]=new int[or-1];
     long int sum=0;//........this is the sum of the det
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
     /*            ³
	  //.........print it
	  for(i=0;i<or-1;i++)
	   {
	    cout<<"\n";
	    for(int j=0;j<or-1;j++)
		 cout<<det2[i][j];
	   }
       */

	}//........take row of big det one by one to find value
     return(sum);
  }//...........if det if of order larger than 1
}