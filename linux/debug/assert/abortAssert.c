#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NDEBUG 1
#include <assert.h>

double my_sqrt(double x){
        assert(x >= 0);
        return sqrt(x);
}

int main(void){
        printf("sqrt +2 = %g\n",my_sqrt(3.0));
        printf("sqrt -2 = %g\n",my_sqrt(-3.0));
        return 0;
}
