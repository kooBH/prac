#include <iostream>

using namespace std;

class P{
  public:
    ~P(){
      cout<<"~P\n";
    }
};

class C : public P{
  public :
    ~C(){
      cout<<"~C\n";
    }
};

int main(){

  C cc;

  return 0;
}

