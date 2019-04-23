#include <iostream>

using namespace std;


class t{
  public:
    int &vv;
    void inc(int&xx){
     vv = xx;
     
    }
};

int main(){
  t tt;
  int a = 33;
  tt.inc(a);
return 0;
}

