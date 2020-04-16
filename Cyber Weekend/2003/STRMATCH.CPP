#include<iostream.h>
#include<string.h>
#include<fstream.h>
class fraction{
	 int dr,nr;
 public:
	 friend ostream& operator<<(ostream& ostr,fraction&);
	 fraction(int x=1,int y=1){
		dr=y;nr=x;
		if(check()==0)cout<<"Wrong fraction...";
		reduce();
	 }
	 int abso(int a){
		if(a<0)return(-a);
		return(a);
	 }
	 void reduce(){
		if(dr<0){
			if(nr>0){ dr=-dr;
					nr=-nr;
				   }
			else if(nr<0)	{ nr=-nr;
						  dr=-dr;
						}
		}
		if(nr==0)dr=1;
		int gcd=1;
		for(int i=(abso(nr)<dr?abso(nr):dr);i>1;i--){
			if(abso(nr)%i==0 && dr%i==0){  gcd=i;break;}
		}
		nr=nr/gcd;
		dr=dr/gcd;
	 }
	 int check(){
		if(dr==0){
			return(0);
		}
		return(1);
	 }
};
ostream& operator<<(ostream& ostr,fraction& fr){
		ostr<<fr.nr;
		if(fr.dr!=1)ostr<<"/"<<fr.dr;
		return ostr;
}
void main(){
	char str1[30],str2[30];
	char main1[100],main2[100];
	int l1,l2,i;
	ifstream infile;
	infile.open("strip.txt");
	ofstream outfile;
	outfile.open("strop.txt");
	while(1){
		infile>>str1;
		if(str1[0]=='-')goto end;
		infile>>str2;
		l1=strlen(str1);
		l2=strlen(str2);
		for(i=0;i<(l1+2*l2);i++){
			if(i>=l2&&i<=(l1+l2-1))
				main1[i]=str1[i-l2];
			else main1[i]=' ';
			if(i<=(l2-1))main2[i]=str2[i];
			else main2[i]=' ';
		}
		int greatest=0;
		for(i=0;i<=l1+l2;i++){
			int cou=0;
			for(int j=0;j<(l1+2*l2);j++)
				if(main1[j]==main2[j])
					if(main1[j]!=' ')cou++;
			if(cou>greatest)greatest=cou;

			//....right shift the main2
			for(j=(l1+2*l2-1);j>0;j--){
				main2[j]=main2[j-1];
			}
			main2[0]=' ';
		}
		fraction fr1(greatest*2,l1+l2);
		outfile<<"appx("<<str1<<","<<str2<<") = "<<fr1<<"\n";
	}
end: infile.close();
	outfile.close();
}