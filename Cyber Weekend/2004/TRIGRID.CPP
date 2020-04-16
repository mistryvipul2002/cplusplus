#include<iostream.h>
#include<fstream.h>
#include<io.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int level(int n){
	int level=1,lastno=1;
	while(1){
		if(n<=lastno && n>=lastno-level+1) return(level);
		level++;
		lastno+=level;
	}
}
void swap(int &a,int &b){
	int temp=a;
	a=b;
	b=temp;
}
int upleft(int n){
	return(n-level(n));
}
int upright(int n){
	return(n-level(n)+1);
}
int downleft(int n){
	return(n+level(n));
}
int downright(int n){
	return(n+level(n)+1);
}
void sort(int *arr,int cou){
	int min,pos;
	for(int i=0;i<cou;i++){
		min=arr[i];
		pos=i;
		for(int j=i+1;j<cou;j++){
			if(arr[j]<min){
				min=arr[j];
				pos=j;
			}
		}
		swap(arr[i],arr[pos]);
	}
}
void main(){
	ofstream outfile;
	ifstream infile;
	infile.open("tri.in");
	outfile.open("tri.out");

	int cou=0;
	int arr[6],arrinput[6];

	char str[40],tempstr[8];
	int len=0,ctemp;

  while(!infile.eof()){
	//......read next line
	infile.getline(str,40);
	len=strlen(str);
	str[len]=' ';
	str[len+1]='\0';

	//.......we get a line in tempstr
	cou=0;
	for(int c=0;c<strlen(str);c++){
		ctemp=0;
		while(str[c]>='0' && str[c]<='9')
			tempstr[ctemp++]=str[c++];
		tempstr[ctemp]='\0';
		arr[cou]=arrinput[cou]=atoi(tempstr);
		cou++;
	}

	//.......sort the array "arr"
	sort(arr,cou);

	//.........check if all pts are distinct
	for(int i=0;i<cou;i++)
		for(int j=i+1;j<cou;j++){
			if(arr[j]==arr[i]){
				goto err;
			}
		}

	//....now cou is the no. of values in arr[]
	if(cou==3){	//...triangle check
		//....triangle up
		if(level(arr[0])==level(arr[1])){
			int dist=arr[1]-arr[0];
			int temp0=arr[0];
			for(int i=0;i<dist;i++){
				temp0=downright(temp0);
			}
			if(temp0==arr[2]){
				for(i=0;i<cou;i++)outfile<<arrinput[i]<<" ";
				outfile<<"are the vertices of a triangle\n";
			}
			else goto err;
		}
		//.........triangle down
		else {
			int dist=arr[2]-arr[1];
			int temp1=arr[1];
			for(int i=0;i<dist;i++){
				temp1=upright(temp1);
			}
			if(temp1==arr[0]){
				for(i=0;i<cou;i++)outfile<<arrinput[i]<<" ";
				outfile<<"are the vertices of a triangle\n";
			}
			else goto err;
		}
	}
	else if(cou==4){	//...parallelogram check
		//........horizontal ||gm
		if(level(arr[0])==level(arr[1])){
			int dist=arr[1]-arr[0];
			int temp0=arr[0],temp1=arr[1],temp00=arr[0],temp11=arr[1];
			for(int i=0;i<dist;i++){
				temp0=downleft(temp0);
				temp1=downleft(temp1);
				temp00=downright(temp00);
				temp11=downright(temp11);
			}
			if((temp0==arr[2] && temp1==arr[3])||(temp00==arr[2] && temp11==arr[3])){
				for(i=0;i<cou;i++)outfile<<arrinput[i]<<" ";
				outfile<<"are the vertices of a parallelogram\n";
			}
			else goto err;
		}
		//...........vertical ||gm
		else if(level(arr[1])==level(arr[2])){
				int dist=arr[2]-arr[1];
				int temp1up=arr[1],temp1down=arr[1];
				for(int i=0;i<dist;i++){
					temp1up=upright(temp1up);
					temp1down=downright(temp1down);
				}
				if((temp1up==arr[0]) && (temp1down==arr[3])){
					for(i=0;i<cou;i++)outfile<<arrinput[i]<<" ";
					outfile<<"are the vertices of a parallelogram\n";
				}
				else goto err;
		}
		else goto err;
	}
	else if(cou==6){	//...hexagon check
		//........horizontal hexagon
		if(level(arr[2])==level(arr[3])){
			int dist=(arr[3]-arr[2])/2;
			int temp2up=arr[2],temp2down=arr[2],temp3up=arr[3],temp3down=arr[3];
			for(int i=0;i<dist;i++){
				temp2up=upright(temp2up);
				temp2down=downright(temp2down);
				temp3up=upleft(temp3up);
				temp3down=downleft(temp3down);
			}
			if(temp2up==arr[0] && temp2down==arr[4] && temp3up==arr[1] && temp3down==arr[5]){
				for(i=0;i<cou;i++)outfile<<arrinput[i]<<" ";
				outfile<<"are the vertices of a hexagon\n";
			}
			else goto err;
		}
		else goto err;
	}
	else {	//....error
err:		for(int i=0;i<cou;i++)outfile<<arrinput[i]<<" ";
		outfile<<"are not the vertices of an acceptable figure\n";
	}
  }
	infile.close();
	outfile.close();
}