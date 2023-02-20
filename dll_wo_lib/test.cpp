#include "wrapper.h"
#include "windows.h"

int main(){
  LoadLibrary("lib_sample.dll");

  extern_func();

  return 0;
}