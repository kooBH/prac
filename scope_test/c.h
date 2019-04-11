#ifndef _H_
#define _H_
#include <iostream>

using namespace std;

int value;

class a{
private:
  int * v;
public :
  a();
  void inc();
  void tell();
};

class b{

private:
  int * v;
  public :
    b();
    void inc();
  void tell();
};

#endif
