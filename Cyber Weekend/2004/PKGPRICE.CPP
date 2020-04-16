#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX_PKGS 50
#define MAX_REQS 50
#define TRUE 1
#define FALSE 0
void main(){
	ofstream outfile;
	ifstream infile;
	infile.open("pack.in");
	outfile.open("pack.out");

	//............read data of packages
	int no_of_pkgs;
	infile>>no_of_pkgs;

	struct package{
		int cat_no;
		float pkg_price;
		int a,b,c,d;
	}pkg[MAX_PKGS];

	int cou=0;
	char ch;
	while(!infile.eof()){
		infile>>pkg[cou].cat_no>>pkg[cou].pkg_price;
		pkg[cou].a=pkg[cou].b=pkg[cou].c=pkg[cou].d=0;
		while(1){
			ch=infile.get();
			if(ch==' ')continue;
			else if(ch=='\n')break;
			else{
				if(ch=='a')infile>>pkg[cou].a;
				if(ch=='b')infile>>pkg[cou].b;
				if(ch=='c')infile>>pkg[cou].c;
				if(ch=='d')infile>>pkg[cou].d;
			}
		}
		cou++;
		if(cou==no_of_pkgs)break;
	}

	//....sort the pkgs acc. to their catalog numbers
	int min,pos;
	for(int i=0;i<cou;i++){
		min=pkg[i].cat_no;
		pos=i;
		for(int j=i+1;j<cou;j++){
			if(pkg[j].cat_no<min){
				min=pkg[j].cat_no;
				pos=j;
			}
		}
		package temp;
		temp=pkg[i];
		pkg[i]=pkg[pos];
		pkg[pos]=temp;
	}

	//.....read the data of user requirements
	int no_of_reqs;
	infile>>no_of_reqs;

	struct {
		int a,b,c,d;
	}reqs[MAX_REQS];

	cou=0;
	ch=infile.get();
	while(!infile.eof()){
		reqs[cou].a=reqs[cou].b=reqs[cou].c=reqs[cou].d=0;
		while(1){
			if(infile.eof())break;
			ch=infile.get();
			if(ch==' ')continue;
			else if(ch=='\n')break;
			else{
				if(ch=='a'){
					int n;
					infile>>n;
					reqs[cou].a+=n;
				}
				if(ch=='b'){
					int n;
					infile>>n;
					reqs[cou].b+=n;
				}
				if(ch=='c'){
					int n;
					infile>>n;
					reqs[cou].c+=n;
				}
				if(ch=='d'){
					int n;
					infile>>n;
					reqs[cou].d+=n;
				}
			}
		}
		cou++;
	}

	//....now our main work begins
	int possibility[MAX_PKGS];
	for(i=0;i<no_of_reqs;i++){	//.....for each requirement do
		for(int j=0;j<no_of_pkgs;j++)	possibility[j]=0;

		int reqa=reqs[i].a;
		int reqb=reqs[i].b;
		int reqc=reqs[i].c;
		int reqd=reqs[i].d;

		for(j=0;j<no_of_pkgs;j++){
			int ava=pkg[j].a;
			int avb=pkg[j].b;
			int avc=pkg[j].c;
			int avd=pkg[j].d;

			if(reqa==0 || ava==0)possibility[j]=possibility[j]>0?possibility[j]:0;
			else if(reqa<=ava)possibility[j]=possibility[j]>1?possibility[j]:1;
			else while(ava*possibility[j]<reqa)++possibility[j];

			if(reqb==0 || avb==0)possibility[j]=possibility[j]>0?possibility[j]:0;
			else if(reqb<=avb)possibility[j]=possibility[j]>1?possibility[j]:1;
			else while(avb*possibility[j]<reqb)++possibility[j];

			if(reqc==0 || avc==0)possibility[j]=possibility[j]>0?possibility[j]:0;
			else if(reqc<=avc)possibility[j]=possibility[j]>1?possibility[j]:1;
			else while(avc*possibility[j]<reqc)++possibility[j];

			if(reqd==0 || avd==0)possibility[j]=possibility[j]>0?possibility[j]:0;
			else if(reqd<=avd)possibility[j]=possibility[j]>1?possibility[j]:1;
			else while(avd*possibility[j]<reqd)++possibility[j];
		}

		//..now we got the upper limits on
		//..the number each pkg can go in multiple in "possibility[]"
		int loop[MAX_PKGS];	//.....shows current selection of packages
		for(j=0;j<no_of_pkgs;j++)loop[j]=0;

		int cur_loop=no_of_pkgs-1;
		float min_price=0.0;
		float min_array[MAX_PKGS];
		int firsttime=TRUE;

again:
		//...run the loop for last package upto the possibility
		while(loop[cur_loop]<=possibility[cur_loop]){
			//.....we get multiple of each package in "loop"
			//.....first check if it satisfy the requirement
			int tota=0,totb=0,totc=0,totd=0;
			for(int t=0;t<no_of_pkgs;t++){ //....find total a's, b's,...
				tota+=pkg[t].a*loop[t];
				totb+=pkg[t].b*loop[t];
				totc+=pkg[t].c*loop[t];
				totd+=pkg[t].d*loop[t];
			}
			//........if combining all this pkgs also can't satisfy reqs
			if(tota<reqs[i].a||totb<reqs[i].b||totc<reqs[i].c||totd<reqs[i].d)  ;	//...do nothing
			else{	//....if reqs are satisfied
				//....find the minimum cost for correct combination
				float price=0.0;
				for(t=0;t<no_of_pkgs;t++)
					price+=pkg[t].pkg_price*loop[t];
				if(firsttime==TRUE){
					min_price=price;
					//...store the values of loop also corresponding to minimum price
					for(int y=0;y<no_of_pkgs;y++)min_array[y]=loop[y];
					firsttime=FALSE;
				}
				else{
					if(min_price>price){
						//...store the values of loop also corresponding to minimum price
						for(int y=0;y<no_of_pkgs;y++)min_array[y]=loop[y];
						min_price=price;
					}
					firsttime=FALSE;
				}
			}
			loop[cur_loop]++;
		}
		//.....make it 0 to make it start again next time
		loop[cur_loop]=0;

		//.....adjust values of loop[]
		while(1){
			if(cur_loop-1>=0)--cur_loop;	//...go one pkg up
			else{	//....end of all iterations; print output
				outfile<<i+1<<": ";
				outfile.precision(2);
				outfile<<min_price;

				long n=min_price*100;
				if(n%10==0 && ((n/10)%10==0))outfile<<".00";
				else if(n%10==0)outfile<<"0";
				outfile<<" ";

				for(int y=0;y<no_of_pkgs;y++){
					//...min_array contains no of each pkg
					if(min_array[y]==0)continue;
					outfile<<pkg[y].cat_no;
					if(min_array[y]>1)outfile<<"("<<min_array[y]<<")";
					outfile<<" ";
				}
				outfile<<"\n";
				goto againfor;
			}
			if(loop[cur_loop]==possibility[cur_loop]){
				loop[cur_loop]=0;
			}
			else{
				loop[cur_loop]+=1;
				break;
			}
		}
		cur_loop=no_of_pkgs-1;
		goto again;
againfor:
	}

	infile.close();
	outfile.close();
}
/*
5
10 25.00 b 2
502 17.95 a 1
3 13.00 c 1
55 27.50 b 1 d 2 c 1
6 52.87 a 2 b 1 d 1 c 3
6
d 1
b 3
b 3 c 2
b1 a 1 c 1 d 1 a 1
b 1 b 2 c 3 c 1 a 1 d 1
b 3 c 2 d 1 c 1 d 2 a 1*/