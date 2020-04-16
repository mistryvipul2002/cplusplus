#include<iostream.h>
#include<conio.h>
void perm(char *str,int start,int end);
void main(){
	clrscr();
	perm("Vipul",0,4);
	getch();
}
void perm(char *str,int k,int n){
	if(k==n){
		cout<<str<<"\t";
		return;
	}
	char t;
	for(int i=k;i<=n;i++){
		t=str[k];str[k]=str[i];str[i]=t;
		perm(str,k+1,n);
		t=str[k];str[k]=str[i];str[i]=t;
	}
}