#include "A.h"
#include "B.h"

A::A() {
  printf("Constructor of A\n");
  B b;
}

A::~A() {
  printf("Destructor of A\n");
}

void A::func() {
  printf("func of A\n");
}