#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define frand() (rand() / (RAND_MAX + 1.0))

int main(int argc, char* argv[])
{
    double sum, sumlinear;
    double x;
    int i;


    for (int i = 1; sum = 0; i++)
    {
        sum += sin(frand() * M_PI);
        //print normalized
        printf("MC:\t%d:\t%f\n", i, M_PI * sum / i);


        ///P^{-1}(x') = (pi/2) * sqrt(x')
        //x = ((M_PI...
        sumlinear += ((M_PI/ 2.0) * sqrt(x)) / ((8 * x) / (M_PI * M_PI));
        // print normalized
        printf("Linear:\t %f\n", sumlinear / i);
    }

    return 0;
}