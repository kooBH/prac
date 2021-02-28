#include <stdlib.h>
#include <stdio.h>

int main(){
	unsigned char bit_a = 0b00000000;

	unsigned char bit_1 = 0b000'0001;
	unsigned char bit_2 = 0b000'0010;

	unsigned char bit_t1,bit_t2;

	bit_t1 = bit_a;
	bit_t2 = bit_a;

	bit_t1 |= 0b000'0001;
	bit_t2 |= 0b000'0011;

	printf("%d\n",bit_t1 | bit_2);
	printf("%d\n",bit_t2 & bit_2);
	printf("%d\n",bit_1 & bit_2);
	printf("%d\n",bit_1 | bit_2);

	return 0;
}
