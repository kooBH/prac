#include "c.h"


//extern int value;

b::b(){
v = &value;
}
void b::inc(){
 *v +=3;
}

void b::tell(){
cout<<*v<<endl;
}
