//......Program by Vipul Mistry for finding two numbers x and y
//......where x is a number which has least significant number as 1
//......and y is the number x multiplied by 2
//......both x and y must be of five digits exactly and
//......cover all the digits from 0 to 9 together
#include<iostream.h>
#include<fstream.h>
void perm(int *,int,int);
void permrem();
int rem[]={0,0,0,0,0,0};
int flag[10]={0,0,0,0,0,0,0,0,0,0};
int x1,x2,x3,x4,x5=1;
int y1,y2,y3,y4,y5=2;
long int x=0,y=0;
long int counter=0;
int caseis=0;
ofstream outfile;
void main(){
//     clrscr();
	outfile.open("digiop.txt");
	flag[1]=flag[2]=1;
	//......x5 and y5 are fixed
	//.........case 1 of 4,x,x,x,1 and 8/9,x,x,0/6,2
	caseis=1;
	x1=4;flag[4]=1;
	for(y1=8;y1<=9;y1++){
		flag[y1]=1;
		for(int i=0;i<2;i++){
			if(i==0){y4=0;flag[0]=1;}
			if(i==1){y4=6;flag[6]=1;}
			permrem();
			if(i==0)flag[0]=0;
			if(i==1)flag[6]=0;
		}
		flag[y1]=0;
	}
	flag[4]=0;
	//..........next case for 3,4,x,5,1 and 6,9,x,0,2
	caseis=2;
	x1=3;flag[3]=1;

	y1=6;y2=9;x2=4;x4=5;y4=0;
	flag[6]=flag[9]=flag[4]=flag[5]=flag[0]=1;
	for(x3=7;x3<=8;x3++){
		flag[x3]=1;
		permrem();
		flag[x3]=0;
	}
	flag[6]=flag[9]=flag[4]=flag[5]=flag[0]=flag[3]=0;

	//.......case for 3,x,x,x,1 and 7,x,x,0/6/8,2
	caseis=3;
	y1=7;flag[7]=1;
	x1=3;flag[3]=1;
	for(int i=0;i<3;i++){
		if(i==0){	y4=0;flag[0]=1;}
		if(i==1){	y4=6;flag[6]=1;}
		if(i==2){	y4=8;flag[8]=1;}
		permrem();
		if(i==0)flag[0]=0;
		if(i==1)flag[6]=0;
		if(i==2)flag[8]=0;
	}
	flag[7]=flag[3]=0;
//	cout<<"\n\nTotal counters = "<<counter;
}
void permrem(){
			int cou=0;
			for(int i=0;i<10;i++){
				if(flag[i]==0)rem[cou++]=i;
			}
			//....now rem contains six numbers that we have to permute
			//....we have to store those no.s in x2-x4 and y2-y4
			perm(rem,0,cou-1);
}
void perm(int *a,int k,int n){
	if(k==n){
		if(caseis==1){
			x2=a[0];x3=a[1];x4=a[2];
			y2=a[3];y3=a[4];
		}
		if(caseis==2){
			y3=a[0];
		}
		if(caseis==3){
			x2=a[0];x3=a[1];x4=a[2];
			y2=a[3];y3=a[4];
		}
		counter++;
		x = x1*10000l+x2*1000+x3*100+x4*10+x5;
		y = y1*10000l+y2*1000+y3*100+y4*10+y5;
		if(y==2*x)outfile<<x<<"\t"<<y<<"\n";
		return;
	}
	int t;
	for(int i=k;i<=n;i++){
		t=a[k];a[k]=a[i];a[i]=t;
		perm(a,k+1,n);
		t=a[k];a[k]=a[i];a[i]=t;
	}
}