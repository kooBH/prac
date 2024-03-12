#include "A.h"

#include <iostream>

class A{

public :
    A();
    void run();

};


A::A(){
    printf("A constructor\n");
    std::cout<<"STD cout\n";
}

void A::run(){
    printf("A run\n");
}


void* A_init(){
    return new A;

}
void A_run(void* obj){
    reinterpret_cast<A*>(obj)->run();
}