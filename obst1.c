#include <stdio.h>

#define MAX 20
#define INF 999999.0

void OptimalBST(int n, float p[], float q[], float E[MAX][MAX], float W[MAX][MAX], int R[MAX][MAX]) {
    int i, j, k, d;
    float cost;

    // Step 1: Initialization
    for (i = 0; i <= n; i++) {
        E[i][i] = q[i];
        W[i][i] = q[i];
        R[i][i] = 0;
    }

    // Step 2: Compute for all intervals of increasing length
    for (d = 1; d <= n; d++) {
        for (i = 0; i <= n - d; i++) {
            j = i + d;
            E[i][j] = INF;
            W[i][j] = W[i][j - 1] + p[j] + q[j];

            // Step 3: Try each key k as root
            for (k = i + 1; k <= j; k++) {
                cost = E[i][k - 1] + E[k][j] + W[i][j];
                if (cost < E[i][j]) {
                    E[i][j] = cost;
                    R[i][j] = k;
                }
            }
        }
    }
}

int main() {
    int n, i, j;
    float p[MAX], q[MAX];
    float E[MAX][MAX], W[MAX][MAX];
    int R[MAX][MAX];

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter successful search probabilities p[1..%d]:\n", n);
    for (i = 1; i <= n; i++)
        scanf("%f", &p[i]);

    printf("Enter unsuccessful search probabilities q[0..%d]:\n", n);
    for (i = 0; i <= n; i++)
        scanf("%f", &q[i]);

    OptimalBST(n, p, q, E, W, R);

    printf("\nMatrix W (Weights):\n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++)
            printf("%7.2f ", W[i][j]);
        printf("\n");
    }

    printf("\nMatrix E (Expected Cost):\n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++)
            printf("%7.2f ", E[i][j]);
        printf("\n");
    }

    printf("\nMatrix R (Roots):\n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++)
            printf("%3d ", R[i][j]);
        printf("\n");
    }

    printf("\nOptimal Cost = %.2f\n", E[0][n]);
    printf("Root of the OBST = %d\n", R[0][n]);

    return 0;
}
