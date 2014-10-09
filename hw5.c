/* 矩陣求解 */
#include <stdio.h>
#define N 256

void upper_solver(double *A, double *x, double *y, int n);
int main(void)
{
        int i, j;
        int n;
        double A[N * (N + 1) / 2];
        double *aptr = A;
        double x[N];
        double y[N];
        scanf("%d", &n);
        for ( i = 0 ; i < n ; i++ )
                for ( j = i ; j < n ; j++ ) {
                        scanf("%lf", aptr);
                        aptr++;
                }
        for ( i = 0 ; i < n ; i++ )
                scanf("%lf", &(y[i]));
        upper_solver(A, x, y, n);

        for ( i = 0 ; i < n ; i++ )
                printf("%lf ", x[i]);

        return 0;
}

void upper_solver(double *A, double *x, double *y, int n)
{
        int i, j;
        double value;
        int a_shift = n * (n + 1) / 2 - 1;
        for (i = n - 1; i >= 0; --i) {
                value = y[i];
                for (j = n - 1; j > i; --j) {
                        value -= x[j] * A[a_shift--];
                }
                x[i] = value / A[a_shift--];
                /* printf("x[%d]: %f, value: %f \n", i, x[i], value); */
        }
}
