
#include <stdio.h>


#ifdef __cplusplus
#define CPP_PREFIX extern "C"
#else
#define CPP_PREFIX
#endif

CPP_PREFIX void* A_init();
CPP_PREFIX void A_run(void*);