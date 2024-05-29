#include <stdio.h>

int main(){

    int numer = 7;
    int denom = 10;

    double result_1 = static_cast<double>(numer) / denom;
    printf("<static_cast>(numer)/denom: %lf\n",result_1);

    double result_2 = numer/ static_cast<double>(denom);
    printf("<static_numer>/cast(denom) : %lf\n",result_2);

    double result_3 = (double)numer / denom;
    printf("(casting)numer/denom: %lf\n",result_1);

    double result_4 = numer / (double)denom;
    printf("numer/(casting)denom: %lf\n",result_1);

    double result_5 = numer / denom;
    printf("numer/denom: %lf\n",result_5);

    return 0;
}