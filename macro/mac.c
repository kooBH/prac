#include <stdio.h>

#define f_idx(_1,_2,_3, _4,...) _4
#define f(...) f_idx(__VA_ARGS__, f3,f2,f1)(__VA_ARGS__)

void f1(int a1){printf("f1\n");}
void f2(int a1,int a2){printf("f2\n");}
void f3(int a1,int a2,int a3){printf("f3\n");}

int main()
{
	f(1);
	f(1,2);
	f(1,2,3);

	return 0;
}
