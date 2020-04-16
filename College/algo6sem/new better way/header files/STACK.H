template <class stacktype>class stack{
	stacktype p[MAX];
	int top;
public:
	stack(){top=-1;}
	void push(stacktype t){
		if(top+1==MAX){cout<<"Can't push....overflow";exit(0);}
		p[++top]=t;
	}
	stacktype pop(){
		if(top==-1){cout<<"Can't pop....";exit(0);}
		return(p[top--]);
	}
	int empty(){
		if(top==-1)return(TRUE);
		return(FALSE);
	}
	stacktype stacktop(){
		return p[top];
	}
};
