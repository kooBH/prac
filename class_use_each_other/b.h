#ifndef _B_
#define _B_

#include <string>
using namespace std;

#include "a.h"



//Foward declaration
class a;


class b{
  public :
  a* parent;

  b(a* par){

    parent = par;

  }

  const string me="b";

};

#endif
