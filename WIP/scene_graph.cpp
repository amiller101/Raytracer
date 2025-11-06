//nodes attachd to a node should be subject tothe saem transformations.
//Use a stack of matrices

typedef double vec3[3];

typedef double matrix[4][4]; // homogenous matrcies allow translation
int matrix_stack_top;

//can hardcode in max (20) or make dynamic with some kind of data structure.
//Realistically 20 would be enough. Fancy cloth simulation wouldn't be done with scene-graphs,
// done seperately then loaded in. That is surface manipulation.
matrix matrix_stack[20];

void matrix_stack_init(void)
{
    matrix_stack_top = 0; // optional
    matrix_stack[0][0][0] = 1.0;
    matrix_stack[0][1][1] = 1.0;
    matrix_stack[0][2][2] = 1.0;
    matrix_stack[0][3][3] = 1.0;
}

void matrix_stack_pop()
{
    if (matrix_stack_top) {
        matrix_stack_top--;
    }
}

void matrix_stack_mul(matrix m)
{
    matrix_stack[matrix_stack_top + 1][0][0] = 
        matrix_stack[matrix_stack_top][0][0] * m[0][0] +
        matrix_stack[matrix_stack_top][0][1] * m[1][0] +
        matrix_stack[matrix_stack_top][0][2] * m[2][0] +
        matrix_stack[matrix_stack_top][0][3] * m[3][0];

        
    matrix_stack[matrix_stack_top + 1][1][0] = 
        matrix_stack[matrix_stack_top][1][0] * m[0][1] +
        matrix_stack[matrix_stack_top][1][1] * m[1][1] +
        matrix_stack[matrix_stack_top][1][2] * m[2][1] +
        matrix_stack[matrix_stack_top][1][3] * m[3][1];

        
    matrix_stack[matrix_stack_top + 1][2][0] = 
        matrix_stack[matrix_stack_top][2][0] * m[0][2] +
        matrix_stack[matrix_stack_top][2][1] * m[1][2] +
        matrix_stack[matrix_stack_top][2][2] * m[2][2] +
        matrix_stack[matrix_stack_top][2][3] * m[3][2];

        
    matrix_stack[matrix_stack_top + 1][3][0] = 
        matrix_stack[matrix_stack_top][3][0] * m[0][3] +
        matrix_stack[matrix_stack_top][3][1] * m[1][3] +
        matrix_stack[matrix_stack_top][3][2] * m[2][3] +
        matrix_stack[matrix_stack_top][3][3] * m[3][3];
        
    //continue

    matrix_stack_top++;

}

void matrix_stack_rotz(){
    double theta = angle * M_PI  /180.0;
    matrix m;

    m[0][0] = cos(theta);
    m[0][1] = -sin(theta);
    m[0][2] = 0;

    m[1][0] = sin(theta);
    m[1][1] = cos (theta);
    m[1][0] = 0;

    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;

    m[3][0] = m[3][1] = m[3][2] = m[2][0] //... = 0

    //matrix_stack_mul(m);


}


void matrix_stack_transform(vec3 out, vec3 in)
{
    out[0] =   (matrix_stack[matrix_stack_top][0][0] * in[0] +
                matrix_stack[matrix_stack_top][0][0] * in[0] +
                matrix_stack[matrix_stack_top][0][0] * in[0] +
                matrix_stack[matrix_stack_top][0][0] * in[0]);
        
}