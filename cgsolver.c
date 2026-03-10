#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int N; // size of A (square) and b 

void matvec(double *A, double *x, double *result, int N)
{
    // row
    for (int m = 0; m < N; m++)
    {
        result[m] = 0.0;
        // column
        for (int n = 0; n < N; n++)
        {
            result[m] += A[m*N + n] * x[n];
        }
    }

}

double dot(double* x, double* y, int N)
{
    double sum = 0.0;

    for (int i = 0; i < N; i++)
    {
        sum += x[i] * y[i];
    }
    return sum;
}

// AI generated
double norm(double *x, int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += x[i] * x[i];
    }
    return sqrt(sum);
}

int main(int argc, char** argv) {


    // =========================
    // AI generated file parsing
    // =========================
    FILE* f = fopen(argv[1], "r");
    if (!f) { printf("can't open %s\n", argv[1]); return 1; }

    fscanf(f, "%d", &N);

    double* A = malloc(sizeof(double) * N * N);
    double* b = malloc(sizeof(double) * N);

    for (int i = 0; i < N * N; i++)
        fscanf(f, "%lf", &A[i]);
    for (int i = 0; i < N; i++)
        fscanf(f, "%lf", &b[i]);

    fclose(f);
    // ===========================


    double* r = malloc(sizeof(double) * N);
    double* r_1 = malloc(sizeof(double) * N);
    double* p = malloc(sizeof(double) * N);

    int k = 0;

    // first guess x is 0 
    double* x = calloc(N, sizeof(double));
    double* Ax = malloc(sizeof(double) * N);



    // r = b - A*x
    matvec(A, x, Ax, N);
    for (int i = 0; i < N; i++)
    {
        r[i] = b[i] - Ax[i];
    }

    if (norm(r,N) < 0.5)
    {
        // print result
        for (int i = 0; i < N; i++)
        {
            printf("resulting x: %f \n", x[i]);
        }
        return 0;
    }
    else
    {

        // initalize p
        for (int i = 0; i < N; i++) 
        {
            p[i] = r[i];
        }
        while (k < 400)
        {


            /*
            just use Ax as a placeholder. Allocating new memory that just holds the same values as Ax and gets updated each iteration seems kinda redundant
            */ 

            // alpha = (rT * dot r)  /  (pT * Ap)
            double num = dot(r,r,N);
            matvec(A,p,Ax,N);
            double denom = dot(p, Ax, N);
            double alpha = num / denom;

            for (int i = 0; i < N; i++)
            {
                x[i] = x[i] + alpha * p[i];
                r_1[i] = r[i] - alpha * Ax[i]; // functionally Ap
            }

            if(norm(r_1,N) < 1e-10)
            {
                break;
            }

            // reuse already computed dot(r,r,N)
            double beta = dot(r_1,r_1,N) / num;


            for (int i = 0; i < N; i++)
            {
                p[i] = r_1[i] + beta * p[i];
                r[i] = r_1[i];
            }

            k++;
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        printf("x[%d]: %f \n", i, x[i]);
    }

    return 0;
}