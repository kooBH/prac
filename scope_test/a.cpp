#include "c.h"


//extern int value;

a::a(){
v = &value;
}
void a::inc(){
  *v +=10;
}

void a::tell(){
cout<<*v<<endl;
}


