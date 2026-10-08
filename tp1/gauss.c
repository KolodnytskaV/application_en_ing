#include <stdio.h>
#include <stdlib.h>

double *gauss(double tab[][3], int n){
    double alpha; 
    double *b = calloc(n, sizeof(double));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b[i] += tab[i][j];
        }
    }

    double s; 

    for(int c = 0; c <= n - 1; c++){
        for(int i = c + 1; i < n; i++){
            alpha = tab[i][c]/tab[c][c];
            for(int j = c; j < n; j++){
                tab[i][j] -= alpha * tab[c][j];
            }
            b[i] -= alpha * b[c];
        }
    }

    double *x=malloc(n*sizeof(double)); 

    for (int i = n - 1; i >= 0; i--){
        s = 0;

        for(int j = i + 1; j < n; j++){
            s += tab[i][j] * x[j];
        }

        x[i] = (b[i] - s)/tab[i][i];
    }

    return x;
}

void affiche(double *tab, int n){
    for(int i = 0; i < n; i++){
        printf("%f\n", tab[i]);
    }
}

int main(){
    double A1[3][3] = {{3, 0, 4}, {7, 4, 2}, {-1, 1, 2}};
    double A2[3][3] = {{-3, 3, -6}, {-4, 7, 8}, {5, 7, -9}};
    double A3[3][3] = {{4, 1, 1}, {2, -9, 0}, {0, -8, 6}};
    double A4[3][3] = {{7, 6, 9}, {4, 5, -4}, {-7, -3, 8}};

    double *X1 = gauss(A1, 3);
    affiche(X1, 3);

    return 0; 
}