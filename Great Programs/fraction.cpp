#include<process.h>
#include<iostream.h>
#include<conio.h>
class fraction{
      int dr,nr;
 public:
      fraction(){
          dr=nr=1;
      }
      fraction(fraction &fr){
           nr=fr.nr;
           dr=fr.dr;
      }
      friend istream& operator>>(istream& istr,fraction&);
      friend ostream& operator<<(ostream& ostr,fraction&);
      friend fraction operator+(fraction,fraction);
      friend fraction operator-(fraction,fraction);
      friend fraction operator*(fraction,fraction);
      friend fraction operator/(fraction,fraction);
      int abso(int a){
          if(a<0)return(-a);
          return(a);
      }
      void reduce(){
          int gcd=1;
          for(int i=(abso(nr)<dr?abso(nr):dr);i>1;i--){
               if(abso(nr)%i==0 && dr%i==0){  gcd=i;break;}
          }
          nr=nr/gcd;
          dr=dr/gcd;
      }
};
fraction operator+(fraction fr1,fraction fr2){
      fraction frnew;
      frnew.nr=fr1.nr*fr2.dr+fr1.dr*fr2.nr;
      frnew.dr=fr1.dr*fr2.dr;
      frnew.reduce();
      return(frnew);
}
fraction operator*(fraction fr1,fraction fr2){
      fraction frnew;
      frnew.nr=fr1.nr*fr2.nr;
      frnew.dr=fr1.dr*fr2.dr;
      frnew.reduce();
      return(frnew);
}
fraction operator/(fraction fr1,fraction fr2){
      fraction frnew;
      frnew.nr=fr1.nr*fr2.dr;
      frnew.dr=fr1.dr*fr2.nr;
      frnew.reduce();
      return(frnew);
}
fraction operator-(fraction fr1,fraction fr2){
      fr2.nr=-fr2.nr;
      return(fr1+fr2);
}
istream& operator>>(istream& istr,fraction &fr){
a:        istr>>fr.nr>>fr.dr;
          if(fr.dr==0){
              cout<<"\nInvalid Fraction...Enter the fraction again...\n";
              goto a;
          }
          if(fr.dr<0){
               if(fr.nr>0){ fr.dr=-fr.dr;
                            fr.nr=-fr.nr;
                          }
               else { fr.nr=-fr.nr;
                      fr.dr=-fr.dr;
                    }
          }
          fr.reduce();
          return(istr);
}
ostream& operator<<(ostream& ostr,fraction& fr){
          return ostr<<fr.nr<<"/"<<fr.dr;
}
void main()
{
  clrscr();
  fraction fr1,fr2;
  cout<<"Enter the fraction in form of nr dr....";
  cin>>fr1;
  cout<<"\nEnter the fraction in form of nr dr....";
  cin>>fr2;
  cout<<"\nThe fraction you entered in reduced form is ....."<<fr1;
  cout<<"\nThe fraction you entered in reduced form is ....."<<fr2;
  cout<<"\nThe sum of two fractions is ...."<<(fr1+fr2);
  cout<<"\nThe diffrence of two fractions is ...."<<(fr1-fr2);
  cout<<"\nThe product of two fractions is ...."<<(fr1*fr2);
  cout<<"\nThe division of two fractions is ...."<<(fr1/fr2);
  getch();
}