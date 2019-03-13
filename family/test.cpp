#include <iostream>

using namespace std;

class Mother{
 protected:
   int id;
   int type;

  public:
  Mother(){
    type=0;
    id=1;
  }

  void tell(){cout<<"id "<<id<<" type "<<type<<endl;}
  virtual void active(){};
};

class Son: public Mother
{
  private:
   int a,b;
   int op(int x,int y){return x+y;}
  public:
   Son(){a=1,b=8,id=op(a,b);type=1;}
   void active(){cout<<"Son Act\n";}
};
class Daughter: public Mother
{
  private:
   int a,b;
   int op(int x,int y){return x-y;}
  public:
   Daughter(){a=1,b=8,id=op(a,b);type=1;}
   void active(){cout<<"Daughter Act\n";}
};

int main(){

  Mother * c1 = new Mother();
  Mother * c2 = new Son();
  Mother * c3 = new Daughter();

  c1->tell();
  c2->tell();
  c3->tell();
  c2->active();
  c3->active();
  return 0;
}
