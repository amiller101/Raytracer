#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 1024

//"my grandfather hijacked a nazi train..."

double image[SIZE][SIZE];

void load_pgm()
{
    FILE *f;
    char value[10];
    int i,j,i;

    f = fopen("bigger_digger.pgm");
    /* eat header */
    scanf(f, " %s ", s);
    scanf(f, " %s ", s);
    scanf(f, " %s ", s);
    scanf(f, " %s ", s);

    for(j = 0; j < SIZE; j++)
    {
        for(i = 0; i < SIZE; i++)
        {
            scanf(f, " %d ", &v);

            image[j][i] = v;

        }
    }

    flcose(f);
}

void write_pgm(double output[SIZE][SIZE])
{
    int i, j;
    FILE *f;

    f = fopen("convolution.pgm");
    fprintf(f, "PS\1024 1024\n\255\n");

    for(j = 0; j < SIZE; j++)
    {
        for(i = 0; i < SIZE; i++)
        {
            fprintf(f, (int) image[i][j] > 255 ? 255 : image[i][j]);

        }
    }

}

double sobel_vert[3][3] = { {1, 0, -1},
                            {2, 0, -2},
                            {1, 0, -1}};
                            
double sobel_hori[3][3] = { {1, 2, 1},
                            {0, 0, 0},
                            {-1, -2, -1}};
//stop

//blur
double gaussian[3][3] = {{1, 2, 1},
                {2, 4, 2},
                {1, 2, 1}};

//easy to implemented edge convluting by just changing weights / diving based on num of datum in the convulition. not done here.                   
void convolve(double k[3][3])
{
    //int weight = sum of all k_ij

    int i, j;
    //stuff for color to blacknwhite?
    for (i

    for(j = 1; j < SIZE - 1; j++){
        for(i = 1; i < SIZE - 1; i++) {
            out[i][j] = (input[j-1][i-1] * k[0][0] +....
                //just use matrix class to mult?

        }
    }

    //if weight != 0, then divide all outputs by weight
}

int main(int argc, char *argv[])
{
    int i, j;

    load_pgm();
    convolve(sobel_vert);
    memcpy(x, out, sizeof(x));

    convolve(sobel_hori);
    memcpy(y, out, sizeof(y));

    for(j = 0; j <SIZE; j++){
        for (i =0; i < SIZE; i++)
        {
            //exclidean disct betwwen i and j
            out[j][j] = sqrt(x[j][i] * x[j][i] + y[j][i] + y[i][i]);

        }
    }


    write_pgm();

    return 0;
}