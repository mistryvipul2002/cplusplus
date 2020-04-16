#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<math.h>
#define DATASET_SIZE 50
int decimal(char *bin){
	int prod=1,sum=0;
	int digit=0,n=strlen(bin)-1;
	do{
		digit = bin[n--]=='0'?0:1;
		sum+=digit*prod;
		prod*=2;
	}while(n>=0);
	return(sum);
}
int checkifall1(char* s){
	for(int i=0;i<strlen(s);i++)
		if(s[i]=='0')return(0);
	return(1);
}
int checkifall0(char* s){
	for(int i=0;i<strlen(s);i++)
		if(s[i]=='1')return(0);
	return(1);
}
void main(){
	ofstream outfile;
	ifstream infile;
	infile.open("cppfil~1\\message.in");
	outfile.open("cppfil~1\\message.out");

	//......read the line from file
	char dataset[DATASET_SIZE],tempstr[80];
	char msg[200];

	msg[0]='\0';dataset[0]='\0';
	infile.getline(tempstr,80);
	strcat(dataset,tempstr);
	while(!infile.eof()){
		infile.getline(tempstr,80);
		strcat(msg,tempstr);
	}

	//........we have got the message
	//......now start decoding it
	int n=0;
	while(n<=strlen(msg)){
		char len[10];int length;
		//....extract next three characters from msg to find length
		len[0]=msg[n++];
		len[1]=msg[n++];
		len[2]=msg[n++];
		len[3]='\0';
		if(checkifall0(len))break;	//....terminate the program if all 0
		length=decimal(len);

		//.....'length' is length of strings we are go'g to read
		while(1){
			//....read in len next string
			for(int i=0;i<length;i++)len[i]=msg[n+i];
			len[i]='\0';
			n=n+length;

			if(checkifall1(len))break;	//....check if all are 1 then break

			//......we got the encoded letter in len[]
			int position=	2*(pow(2,length-1)-1) 	-	(length-1)+
						(1+decimal(len))	-
						1;		//......to take care of 0 index
			outfile<<dataset[position];
		}
	}

end:	outfile.close();
	infile.close();
}