#ifndef _A_
#define _A_
#include <iostream>
#include <string>
using namespace std;

#include "b.h"


//Foward declaration
class b;


class a{
  public :
  
    b* child;

  a(){

    child = new b(this);

  }

  void something(){
    cout<<child->me<<endl;
  }

  const string me="a";

};

#endif
